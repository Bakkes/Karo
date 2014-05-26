using engine.wrapper;
using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Components;
using XNAFrontend.Services;
using CommunicationProtocol;

namespace XNAFrontend
{
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class KaroGame : Microsoft.Xna.Framework.Game
	{
		public GraphicsDeviceManager graphics { get; set; }
		public SpriteBatch spriteBatch { get; private set; }
		public KeyboardState keyState { get; private set; }
		public KeyboardState prevKeyState { get; private set; }

		private ICommunication _communication;
		public KaroGameManager KaroGameManager { get; set; }

		public KaroGame()
		{
			graphics = new GraphicsDeviceManager(this);
			Content.RootDirectory = "Content";
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize()
		{
			spriteBatch = new SpriteBatch(GraphicsDevice);
			IsMouseVisible = true;
			Components.Add(new MenuComponent(this));
			prevKeyState = Keyboard.GetState();
			IsMouseVisible = true;

			graphics.PreferredBackBufferWidth = 1280;
			graphics.PreferredBackBufferHeight = 720;
			graphics.ApplyChanges();

			var loading = new BeachBallComponent(this);
			Components.Add(loading);
			Services.AddService(typeof(ILoadingComponent), loading);

			base.Initialize();
		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime)
		{
			keyState = Keyboard.GetState();

			base.Update(gameTime);
			prevKeyState = keyState;
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(Color.Black);
			base.Draw(gameTime);
		}

		public void ConnectTo(System.Net.IPAddress ip, int port)
		{
			DisposeComminucation();
			Client client = new Client(ip, port);
			_communication = client;
			KaroGameManager = new KaroCommunicatedGameManager(_communication);
			client.OnConnectionFailed += ConnectionFailed;
			_communication.StartCommunicating();
			AddGameComponents();
		}

		public void ConnectionFailed()
		{
			Components.Clear();
			Components.Add(new MessageComponent(this, "Failed to connect to server.", "Hit enter to return to the menu", new MenuComponent(this)));
		}

		public void ConnectionSucceed()
		{
			Components.Clear();
			AddGameComponents();
		}

		public void StartOnlineGame(bool isClient)
		{
			if (isClient)
			{
				Components.Add(new ConnectComponent(this));
				return;
			}

			DisposeComminucation();
			_communication = new Server(43594);
			_communication.Connected += ConnectionSucceed;
			KaroGameManager = new KaroCommunicatedGameManager(_communication);
			Components.Add(new MessageComponent(this, "Waiting for opponent...", "Hit enter to cancel", new MenuComponent(this)));
		}

		private void DisposeComminucation()
		{
			if (_communication == null)
			{
				return;
			}

			_communication.CleanUp();
			_communication = null;
		}

		public void StartOfflineGame()
		{
			KaroGameManager = new KaroComputerManager();
			AddGameComponents();
		}

		private void AddGameComponents()
		{
			Board board = new Board(this);
			CameraComponent camera = new CameraComponent(this, board.Position);
			SkyBoxComponent SkyBox = new SkyBoxComponent(this);

			if (Services.GetService(typeof(ICamera)) != null)
			{
				Services.RemoveService(typeof(ICamera));
			}
			Services.AddService(typeof(ICamera), new Camera());

			Components.Add(camera);
			Components.Add(SkyBox);
			Components.Add(board);
		}
	}
}
