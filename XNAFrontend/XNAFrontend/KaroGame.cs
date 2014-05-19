using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Components;
using XNAFrontend.Services;

namespace XNAFrontend
{
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class KaroGame : Microsoft.Xna.Framework.Game
	{
        public GraphicsDeviceManager graphics { get; set; }

		public KaroGameManager KaroGameManager { get; set; }

		private VertexPositionColor[] _vertices;
		private BasicEffect effect;

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
			IsMouseVisible = true;

			CameraComponent camera = new CameraComponent(this);

			Services.AddService(typeof(ICamera), camera);

			KaroGameManager = new KaroGameManager();
            Components.Add(new SkyBoxComponent(this));
            Components.Add(camera);
			Components.Add(new Board(this));

			Vector3 Size = new Vector3(1, 1, 1);
			Vector3 Position = Vector3.Zero;
			_vertices = new VertexPositionColor[36];
			Color color = Color.Red;

			// Calculate the position of the vertices on the top face.
			Vector3 topLeftFront = Position + new Vector3(-1.0f, 1.0f, -1.0f) * Size;
			Vector3 topLeftBack = Position + new Vector3(-1.0f, 1.0f, 1.0f) * Size;
			Vector3 topRightFront = Position + new Vector3(1.0f, 1.0f, -1.0f) * Size;
			Vector3 topRightBack = Position + new Vector3(1.0f, 1.0f, 1.0f) * Size;

			// Calculate the position of the vertices on the bottom face.
			Vector3 btmLeftFront = Position + new Vector3(-1.0f, -1.0f, -1.0f) * Size;
			Vector3 btmLeftBack = Position + new Vector3(-1.0f, -1.0f, 1.0f) * Size;
			Vector3 btmRightFront = Position + new Vector3(1.0f, -1.0f, -1.0f) * Size;
			Vector3 btmRightBack = Position + new Vector3(1.0f, -1.0f, 1.0f) * Size;

			// Add the vertices for the FRONT face.
			_vertices[0] = new VertexPositionColor(topLeftFront, color);
			_vertices[1] = new VertexPositionColor(btmLeftFront, color);
			_vertices[2] = new VertexPositionColor(topRightFront, color);
			_vertices[3] = new VertexPositionColor(btmLeftFront, color);
			_vertices[4] = new VertexPositionColor(btmRightFront, color);
			_vertices[5] = new VertexPositionColor(topRightFront, color);

			// Add the vertices for the BACK face.
			_vertices[6] = new VertexPositionColor(topLeftBack, color);
			_vertices[7] = new VertexPositionColor(topRightBack, color);
			_vertices[8] = new VertexPositionColor(btmLeftBack, color);
			_vertices[9] = new VertexPositionColor(btmLeftBack, color);
			_vertices[10] = new VertexPositionColor(topRightBack, color);
			_vertices[11] = new VertexPositionColor(btmRightBack, color);

			// Add the vertices for the TOP face.
			_vertices[12] = new VertexPositionColor(topLeftFront, color);
			_vertices[13] = new VertexPositionColor(topRightBack, color);
			_vertices[14] = new VertexPositionColor(topLeftBack, color);
			_vertices[15] = new VertexPositionColor(topLeftFront, color);
			_vertices[16] = new VertexPositionColor(topRightFront, color);
			_vertices[17] = new VertexPositionColor(topRightBack, color);

			// Add the vertices for the BOTTOM face. 
			_vertices[18] = new VertexPositionColor(btmLeftFront, color);
			_vertices[19] = new VertexPositionColor(btmLeftBack, color);
			_vertices[20] = new VertexPositionColor(btmRightBack, color);
			_vertices[21] = new VertexPositionColor(btmLeftFront, color);
			_vertices[22] = new VertexPositionColor(btmRightBack, color);
			_vertices[23] = new VertexPositionColor(btmRightFront, color);

			// Add the vertices for the LEFT face.
			_vertices[24] = new VertexPositionColor(topLeftFront, color);
			_vertices[25] = new VertexPositionColor(btmLeftBack, color);
			_vertices[26] = new VertexPositionColor(btmLeftFront, color);
			_vertices[27] = new VertexPositionColor(topLeftBack, color);
			_vertices[28] = new VertexPositionColor(btmLeftBack, color);
			_vertices[29] = new VertexPositionColor(topLeftFront, color);

			// Add the vertices for the RIGHT face. 
			_vertices[30] = new VertexPositionColor(topRightFront, color);
			_vertices[31] = new VertexPositionColor(btmRightFront, color);
			_vertices[32] = new VertexPositionColor(btmRightBack, color);
			_vertices[33] = new VertexPositionColor(topRightBack, color);
			_vertices[34] = new VertexPositionColor(topRightFront, color);
			_vertices[35] = new VertexPositionColor(btmRightBack, color);

			effect = new BasicEffect(GraphicsDevice);

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
			GraphicsDevice.Clear(Color.CornflowerBlue);

			ICamera camera = (ICamera)Services.GetService(typeof(ICamera));
			effect.VertexColorEnabled = true;
			effect.CurrentTechnique.Passes[0].Apply();
			effect.View = camera.View;
			effect.World = camera.World;
			effect.Projection = camera.Projection;

			using (VertexBuffer cubeBuffer = new VertexBuffer(GraphicsDevice, typeof(VertexPositionColor), 36, BufferUsage.None))
			{
				cubeBuffer.SetData<VertexPositionColor>(_vertices);
				GraphicsDevice.SetVertexBuffer(cubeBuffer);
				GraphicsDevice.DrawPrimitives(PrimitiveType.TriangleList, 0, 12);
			}

			base.Draw(gameTime);
		}
	}
}
