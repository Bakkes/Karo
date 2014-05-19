using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Components;

namespace XNAFrontend
{
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class KaroGame : Microsoft.Xna.Framework.Game
	{
        public GraphicsDeviceManager graphics { get; set; }
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
			KaroGameManager = new KaroGameManager();
			Board board = new Board(this);
            board.CameraComponent = new CameraComponent(this);
            SkyBoxComponent SkyBox = new SkyBoxComponent(this);

            SkyBox.CameraComponent = board.CameraComponent;
            Components.Add(SkyBox);
			IsMouseVisible = true;

            Components.Add(board.CameraComponent);
			
			Components.Add(board);
            base.Initialize();
		}

     
		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime)
		{
			// Allows the game to exit
			if (Keyboard.GetState().IsKeyDown(Keys.Escape))
			{
				this.Exit();
			}

			base.Update(gameTime);
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw(GameTime gameTime)
		{
		

			base.Draw(gameTime);
		}
	}
}
