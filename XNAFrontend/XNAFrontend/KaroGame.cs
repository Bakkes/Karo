using System;
using System.Net;
using System.Threading;
using engine.wrapper;
using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Components;
using XNAFrontend.Services;
using CommunicationProtocol;
using System.Diagnostics;
using System.Linq;

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

			if (keyState.IsKeyDown(Keys.Escape) && prevKeyState.IsKeyUp(Keys.Escape))
			{
				Components.Clear();
				Components.Add(new MenuComponent(this));
			}

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
			DisposeCommunication();
			Client client = new Client(ip, port);
			_communication = client;
			KaroGameManager = new KaroCommunicatedGameManager(_communication);

			// Attach handlers
			KaroGameManager.OnPlayerWin += PlayerWon;
			client.OnConnectionFailed += ConnectionFailed;
			AddGlobalHandlers();

			_communication.StartCommunicating();
			AddGameComponents();
		}

		#region Event Handler for Connected Mode
		private void AddGlobalHandlers()
		{
			_communication.Disconnected += Disconnected;
		}

		void Disconnected(DisconnectReason reason)
		{
			Components.Clear();

			string s = "";
			switch (reason) {
				case DisconnectReason.ConnectionLost:
					s = "Lost connection";
					break;

				case DisconnectReason.GameEnded:
					s = "Game ended";
					break;

				case DisconnectReason.InvalidMove:
					s = "Invalid move";
					break;

				case DisconnectReason.WinnerDisputed:
					s = "Winner disputed";
					break;
			}

			Components.Add(new MessageComponent(this, string.Format("Disconnected: {0}", s), "Hit enter to return to the menu", new MenuComponent(this)));
		}

		private void ConnectionFailed()
		{
			Components.Clear();
			Components.Add(new MessageComponent(this, "Failed to connect to server.", "Hit enter to return to the menu", new MenuComponent(this)));
		}

		private void ConnectionSucceed()
		{
			Components.Clear();
			AddGameComponents();
		}

		public void Disconnected()
		{
		}
		#endregion

		public void StartOnlineGame(int modus)
		{
			if (modus == 0) // client
			{
				Components.Add(new ConnectComponent(this));
				return;
			}
			if(modus == 1){ // server
				DisposeCommunication();
				_communication = new Server(43594);
				_communication.Connected += ConnectionSucceed;
				AddGlobalHandlers();
				KaroGameManager = new KaroCommunicatedGameManager(_communication);
				KaroGameManager.OnPlayerWin += PlayerWon;
				Components.Add(new MessageComponent(this, "Waiting for opponent...", "Hit enter to cancel", new MenuComponent(this)));
				return;
			}
			if(modus == 2){
				// play with yourself
				DisposeCommunication();
				if(otherMeServer != null){
					otherMeServer.CleanUp();
				}
				otherMeServer = new Server(43594);
				otherMe = new KaroCommunicatedGameManager(otherMeServer);
				// change number to change openent
				// 0: mimax ai (slowest possible)
				// 1: alfa beta ai
				// 2: moverordering ab ai
				// >=3: move ordering alfa beta transpositiontable ai
				
				// the other me is configurable but connecto ai always uses the best one
				// the best one is with the longest name
				otherMe.Game.SetAI(2);
				otherMe.name = "Messed up ai";
				ConnectTo(IPAddress.Parse("127.0.0.1"), 43594);
			}

		}

		private ICommunication otherMeServer;
		private KaroCommunicatedGameManager otherMe;


		private void PlayerWon(Players player)
		{
			Debug.WriteLine(player + " has won");

			// Get rid of game related components
			Components.Remove(Components.First(c => c is Board));

			string color = player == Players.Max ? "red" : "green";

			// Show the winning screen.
			Components.Add(new MessageComponent(this,
				string.Format("The {0} player has won the game.", color),
				"Hit enter to return to the menu",
				new MenuComponent(this)
			));
		}

		private void DisposeCommunication()
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
			KaroGameManager.OnPlayerWin += PlayerWon;
			AddGameComponents();
		}

		private void AddGameComponents()
		{
			Board board = new Board(this);
			KaroGameManager.OnBoardUpdated += board.ClearMarkCache;
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
			Components.Add(new BeachBallComponent(this));
		}
	}
}
