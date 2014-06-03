using System.Collections.Generic;
using System.Linq;
using System.Threading;
using engine.wrapper;
using KaroManager;
using KaroManager.State;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using XNAFrontend.Services;
using Microsoft.Xna.Framework.Audio;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class Board : ACommonComponent
	{
		const float SIZE = 1f;
		const float GAP = 0.1f;

		private Thread _highlightThread;

		private Texture2D _background;
		private SoundEffect _invalidMoveSound;
		private KaroGame _game;
		private Model _cordModel;
		private Model _tileModel;
		private Model _minModel;
		private Model _maxModel;
		private Dictionary<Vector2, bool> _markedCache;
		private Vector2DWrapper[] _lastMoveHighlight;
		private List<string> _cordList;

		private MouseState _previousMouseState;

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
			_markedCache = new Dictionary<Vector2, bool>();
			_lastMoveHighlight = new Vector2DWrapper[2];
			this.Position = new Vector3((SIZE + GAP) * 2f, 0f, (SIZE + GAP) * 1.5f);
			game.KaroGameManager.OnMoveExecuted += OnMoveExecuted;
			game.KaroGameManager.OnInvalidMoveMade += OnInvalidMove;
			_highlightThread = new Thread(RemoveHighlightAfterOneSecond);
			_game = game;
			LoadContent();
		}

		public override void Initialize()
		{
			base.Initialize();
			this._previousMouseState = Mouse.GetState();

			_cordList = new List<string>();
			_cordList.Add("a");
			_cordList.Add("b");
			_cordList.Add("c");
			_cordList.Add("d");
			_cordList.Add("e");
			_cordList.Add("f");
			_cordList.Add("g");
			_cordList.Add("h");
			_cordList.Add("i");
			_cordList.Add("j");
			_cordList.Add("k");
			_cordList.Add("l");
			_cordList.Add("m");
			_cordList.Add("n");
			_cordList.Add("o");
			_cordList.Add("p");
			_cordList.Add("q");
			_cordList.Add("r");
			_cordList.Add("s");
			_cordList.Add("t");
		}

		protected override void LoadContent()
		{
			base.LoadContent();
			_tileModel = Game.Content.Load<Model>("tile");
			_cordModel = Game.Content.Load<Model>("cords");
			_minModel = Game.Content.Load<Model>("piecemin");
			_maxModel = Game.Content.Load<Model>("piecemax");
			_invalidMoveSound = Game.Content.Load<SoundEffect>("invalidmove");
			_background = Game.Content.Load<Texture2D>("background");
		}

		public override void Update(GameTime gameTime)
		{
			MouseState mouseState = Mouse.GetState();
			if (mouseState.LeftButton == ButtonState.Pressed && _previousMouseState.LeftButton != ButtonState.Pressed)
			{
				Vector2 tilePosition = GetTileAtPixelPosition(mouseState.X, mouseState.Y);
				if (tilePosition.X != -1337)
				{
					karoGame.KaroGameManager.Update(
						new System.Drawing.Point((int)tilePosition.X, (int)tilePosition.Y)
					);
				}
			}

			if (mouseState.RightButton == ButtonState.Pressed)
			{
				_markedCache = new Dictionary<Vector2, bool>();
				KaroGameManager.Update(new System.Drawing.Point(-1337, -1337));
			}

			base.Update(gameTime);

			_previousMouseState = mouseState;
		}

		protected Vector2 GetTileAtPixelPosition(int mouseX, int mouseY)
		{
			_markedCache = new Dictionary<Vector2, bool>();
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Vector3 nearSource = new Vector3((float)mouseX, (float)mouseY, 0f);
			Vector3 farSource = new Vector3((float)mouseX, (float)mouseY, 1f);
			Matrix world = Matrix.CreateTranslation(0, 0, 0);
			Vector3 nearPoint = GraphicsDevice.Viewport.Unproject(nearSource,
				camera.Projection, camera.View, world);
			Vector3 farPoint = GraphicsDevice.Viewport.Unproject(farSource,
				camera.Projection, camera.View, world);

			Vector3 direction = farPoint - nearPoint;
			direction.Normalize();
			Ray pickRay = new Ray(nearPoint, direction);

			float nearestDist = float.MaxValue;
			Vector2 nearest = new Vector2(-1337, -1337);

			for (int x = -1; x <= 20; x++)
			{
				for (int y = -1; y <= 20; y++)
				{
					BoundingBox b = Utilities.CreateBoundingBox(
						_tileModel, world * Matrix.CreateTranslation(
							new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP))
						)
					);
					float? dist = pickRay.Intersects(b);
					if (dist != null && dist > 0 && dist < nearestDist)
					{
						nearestDist = (float)dist;
						nearest = new Vector2(x, y);
					}
				}
			}
			return nearest;
		}

		public override void Draw(GameTime gameTime)
		{
			Rectangle screenRectangle = new Rectangle(0, 0, 
				GraphicsDevice.PresentationParameters.BackBufferWidth, 
				GraphicsDevice.PresentationParameters.BackBufferHeight);
			karoGame.spriteBatch.Begin();
			karoGame.spriteBatch.Draw(_background, screenRectangle, Color.White);
			karoGame.spriteBatch.End();

			karoGame.GraphicsDevice.DepthStencilState = DepthStencilState.Default;

			BoardWrapper board = KaroGameManager.Board;

			for (int i = -1; i < 20; i++)
			{
				for (int j = -1; i + j < 20; j++)
				{
					CellWrapper cell = board.GetRelativeCellAt(new Vector2DWrapper(i, j));

					if (cell.HasTile())
					{
						DrawCellAt(cell, i, j);
					}
					if (IsMarkedCell(new Vector2((float)i, (float)j)))
					{
						DrawCellAt(cell, i, j, true);
					}
				}
			}

			int width = (int)board.GetDynamicSize().X;
			int height = (int)board.GetDynamicSize().Y;
			CellWrapper tmp = board.GetRelativeCellAt(new Vector2DWrapper(0, 0));

			for (int i = 0; i <= height; i++)
			{
				DrawCordsAt(tmp, -2, i, (i + 1).ToString());
			}
			for (int i = 0; i <= width; i++)
			{
				DrawCordsAt(tmp, i, (int)height + 2, _cordList[i]);
			}

			base.Draw(gameTime);
		}


		private void DrawCordsAt(CellWrapper cell, int x, int y, string cord)
		{
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-90));
			foreach (ModelMesh mesh in _cordModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.TextureEnabled = true;
					effect.Texture = Game.Content.Load<Texture2D>("cords/"+cord);
					effect.EnableDefaultLighting();
					effect.World = world * Matrix.CreateRotationX(MathHelper.ToRadians(90)) * Matrix.CreateScale(0.5f) * Matrix.CreateRotationY(MathHelper.ToRadians(180)) * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
					effect.Alpha = 1f;
					effect.DiffuseColor = new Vector3(0.8f, 0.8f, 0.8f);
				}
				mesh.Draw();
			}
		}

		/// <summary>
		/// Draws a tile with the specified relative position.
		/// </summary>
		private void DrawCellAt(CellWrapper cell, int x, int y, bool marked = false)
		{
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-90));
			bool clickableTile = IsMarkedCell(new Vector2((float)x, (float)y));
			foreach (ModelMesh mesh in _tileModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.LightingEnabled = true;
					effect.DirectionalLight0.Enabled = true;
					effect.DirectionalLight0.DiffuseColor = new Vector3(0.5f, 0.2f, 0f);
					effect.DirectionalLight0.Direction = new Vector3(1f, -1f, 1f);
					effect.DirectionalLight0.SpecularColor = new Vector3(0f, 1f, 0f);
					effect.DirectionalLight1.Enabled = true;
					effect.DirectionalLight1.DiffuseColor = new Vector3(0.7f, 0.7f, 0.7f);
					effect.DirectionalLight1.Direction = new Vector3(1f, -1f, 1f);
					effect.DirectionalLight1.SpecularColor = new Vector3(0f, 1f, 0f);
					effect.World = world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), 0, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
					if (marked)
					{
						effect.Alpha = 0.2f;
					}
					else
					{
						effect.Alpha = 1f;
					}
					if (_lastMoveHighlight[0] != null && _lastMoveHighlight[0] == cell.GetRelativePosition())
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 0f);
					}
					else if (_lastMoveHighlight[1] != null && _lastMoveHighlight[1] == cell.GetRelativePosition())
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 0f);
					}
					else if (clickableTile || marked)
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 1f);
					}
					else
					{
						effect.DiffuseColor = new Vector3(0.5f, 0.5f, 0.5f);
					}
				}
				mesh.Draw();
			}

			if (!cell.IsEmpty())
			{
				DrawPieceAt(cell, x, y);
			}
		}

		private void DrawPieceAt(CellWrapper cell, int x, int y)
		{
			// Nothing to draw if this cell is empty.
			if (cell.IsEmpty()) { return; }

			// Define the model of the piece we have to use (max/min).
			Model pieceModel = cell.IsMaxPiece() ? _maxModel : _minModel;
			Vector3 color = cell.IsMaxPiece() ? Color.Red.ToVector3() : Color.Green.ToVector3();
			ICamera camera = (ICamera)Game.Services.GetService(typeof(ICamera));
			Matrix[] transforms = new Matrix[_tileModel.Bones.Count];
			_tileModel.CopyAbsoluteBoneTransformsTo(transforms);
			bool marked = false;
			if (KaroGameManager.CurrentMove != null)
			{
				marked = KaroGameManager.CurrentMove.GetFromCell() ==
					cell.GetRelativePosition();
			}

			// Flip the piece if neccesary
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-270));
			if (cell.IsFlipped())
			{
				world *= Matrix.CreateRotationX(MathHelper.ToRadians(180));
			}

			BoundingBox pieceBox = Utilities.CreateBoundingBox(pieceModel, world);
			BoundingBox tileBox = Utilities.CreateBoundingBox(pieceModel, world);
			float extraHeight = pieceBox.Max.Y / 2 + tileBox.Max.Y;

			// Draw the piece on the cell.
			foreach (ModelMesh mesh in pieceModel.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.LightingEnabled = true;
					effect.DirectionalLight0.Enabled = true;
					effect.DirectionalLight0.DiffuseColor = new Vector3(0.5f, 0.2f, 0f);
					effect.DirectionalLight0.Direction = new Vector3(1f, -1f, 1f);
					effect.DirectionalLight0.SpecularColor = new Vector3(0f, 1f, 0f);
					effect.DirectionalLight1.Enabled = true;
					effect.DirectionalLight1.DiffuseColor = new Vector3(0.7f, 0.7f, 0.7f);
					effect.DirectionalLight1.Direction = new Vector3(1f, -1f, 1f);
					effect.DirectionalLight1.SpecularColor = new Vector3(0f, 1f, 0f);
					effect.World = world * Matrix.CreateTranslation(new Vector3(x * (SIZE + GAP), extraHeight, y * (SIZE + GAP)));
					effect.View = camera.View;
					effect.Projection = camera.Projection;
					if (marked)
					{
						effect.DiffuseColor = new Vector3(1f, 1f, 0f);
					}
					else
					{
						effect.DiffuseColor = color;
					}
				}
				mesh.Draw();
			}
		}

		private bool IsMarkedCell(Vector2 position)
		{
			lock (_markedCache)
			{
				if (_markedCache.ContainsKey(position))
				{
					return _markedCache[position];
				}
				_markedCache[position] = false;

				BoardWrapper board = KaroGameManager.Board;
				MoveWrapper currentMove = KaroGameManager.CurrentMove;
				IKaroState currentState = KaroGameManager.CurrentState;

				if (currentState is PlaceState)
				{
					foreach (MoveWrapper legalMove in KaroGameManager.FindLegalMoves(KaroGameManager.CurrentPlayer))
					{
						Vector2DWrapper wrapperPos = legalMove.GetToCell();
						if (position == new Vector2((float)wrapperPos.X, (float)wrapperPos.Y))
						{
							_markedCache[position] = true;
						}
					}
				}
				else if (currentState is PieceSourceState)
				{
					foreach (MoveWrapper legalMove in KaroGameManager.FindLegalMoves(KaroGameManager.CurrentPlayer))
					{
						Vector2DWrapper wrapperPos = legalMove.GetFromCell();
						if (position == new Vector2((float)wrapperPos.X, (float)wrapperPos.Y))
						{
							_markedCache[position] = true;
						}
					}
				}
				else if (currentState is PieceDestinationState)
				{
					foreach (MoveWrapper legalMove in KaroGameManager.FindLegalMoves(KaroGameManager.CurrentPlayer)
						.Where(m => m.GetFromCell() == currentMove.GetFromCell()))
					{
						Vector2DWrapper wrapperPos = legalMove.GetToCell();
						if (position == new Vector2((float)wrapperPos.X, (float)wrapperPos.Y))
						{
							_markedCache[position] = true;
						}
					}
				}
				else if (currentState is CellSourceState)
				{
					foreach (MoveWrapper legalMove in KaroGameManager.FindLegalMoves(KaroGameManager.CurrentPlayer)
						.Where(m => m.GetFromCell() == currentMove.GetFromCell())
						.Where(m => m.GetToCell() == currentMove.GetToCell()))
					{
						Vector2DWrapper wrapperPos = legalMove.GetUsedCell();
						if (position == new Vector2((float)wrapperPos.X, (float)wrapperPos.Y))
						{
							_markedCache[position] = true;
						}
					}
				}

				return _markedCache[position];
			}
		}

		private void OnInvalidMove()
		{
			_invalidMoveSound.Play();
		}

		private void OnMoveExecuted(MoveWrapper move)
		{
			if (move.GetMoveType() == MoveType.INSERT)
			{
				_lastMoveHighlight[0] = move.GetToCell();
			}
			else
			{
				_lastMoveHighlight[0] = move.GetFromCell();
				_lastMoveHighlight[1] = move.GetToCell();

				// Adjust coordinates if board moved around.
				if (_lastMoveHighlight[1].X < 0)
				{
					_lastMoveHighlight[0].X++;
					_lastMoveHighlight[1].X++;
				}
				if (_lastMoveHighlight[1].Y < 0)
				{
					_lastMoveHighlight[0].Y++;
					_lastMoveHighlight[1].Y++;
				}
				if (move.HasUsedCell() &&
					karoGame.KaroGameManager.Board.GetRelativeCellAt(
						move.GetUsedCell()).HasTile())
				{
					if (move.GetUsedCell().X == 0 &&
						move.GetToCell().X >= 0 &&
						move.GetToCell().Y >= 0)
					{
						_lastMoveHighlight[0].X--;
						_lastMoveHighlight[1].X--;
					}
					if (move.GetUsedCell().Y == 0 &&
						move.GetToCell().X >= 0 &&
						move.GetToCell().Y >= 0)
					{
						_lastMoveHighlight[0].Y--;
						_lastMoveHighlight[1].Y--;
					}
				}
			}
			if (_highlightThread.IsAlive)
			{
				_highlightThread.Abort();
			}
		    _highlightThread = new Thread(RemoveHighlightAfterOneSecond);
			_highlightThread.Start();
		}

		private void RemoveHighlightAfterOneSecond()
		{
			Thread.Sleep(1000);
			_lastMoveHighlight[0] = null;
			_lastMoveHighlight[1] = null;
		}

		public void ClearMarkCache()
		{
			lock (_markedCache)
			{
				_markedCache = new Dictionary<Vector2, bool>();
			}
		}
	}
}
