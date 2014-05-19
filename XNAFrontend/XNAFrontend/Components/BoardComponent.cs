using engine.wrapper;
using KaroManager;
using XNAFrontend.Services;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
    internal class Board : ACommonComponent
	{
        const float SIZE = 1f;
        const float GAP = 0.1f;

		private Model _tileModel;
	
		private KaroGameManager KaroGameManager
		{
			get
			{
				return karoGame.KaroGameManager;
			}
		}

		public Vector3 Position { get; set; }

		public Board(KaroGame game)
			: base(game)
		{
			LoadContent();
		}

		public override void Initialize()
		{
			base.Initialize();
			this.Position = Vector3.Zero;
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("tile");
		}

		public override void Update(GameTime gameTime)
		{
            
            MouseState mouseState = Mouse.GetState();
            if (mouseState.LeftButton == ButtonState.Pressed)
            {
                

                ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
                int mouseX = mouseState.X;
                int mouseY = mouseState.Y;
                Vector3 nearsource = new Vector3((float)mouseX, (float)mouseY, 0f);
                Vector3 farsource = new Vector3((float)mouseX, (float)mouseY, 1f);

                Matrix world = Matrix.CreateTranslation(0, 0, 0);

                Vector3 nearPoint = GraphicsDevice.Viewport.Unproject(nearsource,
                    camera.Projection, camera.View, world);

                Vector3 farPoint = GraphicsDevice.Viewport.Unproject(farsource,
                    camera.Projection, camera.View, world);

                Vector3 direction = farPoint - nearPoint;
                direction.Normalize();
                Ray pickRay = new Ray(nearPoint, direction);

                for (int x = 0; x <= 20; x++)
                {
                    for (int y = 0; y <= 20; y++)
                    {
                        CellWrapper cell = KaroGameManager.Board.GetRelativeCellAt(new Vector2DWrapper(x, y));
                        if (cell.HasTile())
                        {
                            BoundingBox b = UpdateBoundingBox(_tileModel, world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP))));
                            if (pickRay.Intersects(b) > 0)
                            {
                                System.Console.WriteLine("Found at " + x + ", " + y + ": " + pickRay.Intersects(b));
                            }

                        }
                    }
                }
            }
			base.Update(gameTime);
		}

        protected BoundingBox UpdateBoundingBox(Model model, Matrix worldTransform)
        {
            // Initialize minimum and maximum corners of the bounding box to max and min values
            Vector3 min = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
            Vector3 max = new Vector3(float.MinValue, float.MinValue, float.MinValue);

            // For each mesh of the model
            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (ModelMeshPart meshPart in mesh.MeshParts)
                {
                    // Vertex buffer parameters
                    int vertexStride = meshPart.VertexBuffer.VertexDeclaration.VertexStride;
                    int vertexBufferSize = meshPart.NumVertices * vertexStride;

                    // Get vertex data as float
                    float[] vertexData = new float[vertexBufferSize / sizeof(float)];
                    meshPart.VertexBuffer.GetData<float>(vertexData);

                    // Iterate through vertices (possibly) growing bounding box, all calculations are done in world space
                    for (int i = 0; i < vertexBufferSize / sizeof(float); i += vertexStride / sizeof(float))
                    {
                        Vector3 transformedPosition = Vector3.Transform(new Vector3(vertexData[i], vertexData[i + 1], vertexData[i + 2]), worldTransform);

                        min = Vector3.Min(min, transformedPosition);
                        max = Vector3.Max(max, transformedPosition);
                    }
                }
            }

            // Create and return bounding box
            return new BoundingBox(min, max);
        }

		public override void Draw(GameTime gameTime)
		{
			BoardWrapper board = KaroGameManager.Board;

			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
                    if (i == 20)
                    {
                        continue;
                    }
                    if (j == 20)
                    {
                        break;
                    }
					CellWrapper cell = board.GetRelativeCellAt(new Vector2DWrapper(i, j));
					if (cell.HasTile())
					{
						DrawCellAt(cell, i, j);
					}
				}
			}
			base.Draw(gameTime);
		}

		/// <summary>
		/// Draws a tile with the specified relative position.
		/// </summary>
		private void DrawCellAt(CellWrapper cell, int x, int y)
		{
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-90));
			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
				}

				mesh.Draw();
			}
		}
	}
}
