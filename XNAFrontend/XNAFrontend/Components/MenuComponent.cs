﻿using engine.wrapper;
using KaroManager;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	/// <summary>
	/// 3D board representation of the karo board game.
	/// </summary>
	internal class MenuComponent : ACommonComponent
	{
		private KaroGame game;
		private SpriteFont font;
		private int selectedItem;
		private int menuDepth;

		public MenuComponent(KaroGame game)
			: base(game)
		{
			this.game = game;

			LoadContent();
		}

		public override void Initialize()
		{
			selectedItem = 0;
			menuDepth = 0;

			base.Initialize();
		}

		protected override void LoadContent()
		{
			font = game.Content.Load<SpriteFont>("SpriteFont1");

			base.LoadContent();
		}

		public override void Update(GameTime gameTime)
		{
			if (game.keyState.IsKeyDown(Keys.Down) && game.prevKeyState.IsKeyUp(Keys.Down))
			{
				selectedItem++;
				if (menuDepth == 1 && selectedItem > 1) { selectedItem = 0; }
				if (selectedItem > 2) { selectedItem = 0; }
			}
			if (game.keyState.IsKeyDown(Keys.Up) && game.prevKeyState.IsKeyUp(Keys.Up))
			{
				selectedItem--;
				if (selectedItem < 0) { selectedItem = 2; }
				if (menuDepth == 1 && selectedItem > 1) { selectedItem = 1; }
			}
			if (game.keyState.IsKeyDown(Keys.Enter) && game.prevKeyState.IsKeyUp(Keys.Enter))
			{
				ExecuteMenuItem(menuDepth, selectedItem);
			}
			if (game.keyState.IsKeyDown(Keys.Escape) && game.prevKeyState.IsKeyUp(Keys.Escape))
			{
				if (menuDepth > 0) { selectedItem = 0; menuDepth = 0; }
			}

			base.Update(gameTime);
		}

		private void ExecuteMenuItem(int depth, int item)
		{
			if (item == 0 && depth == 0) { game.StartGame(); game.Components.Remove(this); }
			if (item == 1 && depth == 0) { menuDepth = 1; }
			if (item == 2 && depth == 0) { game.Exit(); }

			if (item == 0 && depth == 1) { game.StartGame(); game.Components.Remove(this); }
			if (item == 1 && depth == 1) { game.StartGame(); game.Components.Remove(this); }

			selectedItem = 0;
		}

		public override void Draw(GameTime gameTime)
		{
			GraphicsDevice.Clear(Color.Black);

			game.spriteBatch.Begin();

			if (menuDepth == 0)
			{
				if (selectedItem == 0) { game.spriteBatch.DrawString(font, "Player vs Computer", new Vector2(100, 150), Color.Green); }
				else { game.spriteBatch.DrawString(font, "Player vs Computer", new Vector2(100, 150), Color.White); }
				if (selectedItem == 1) { game.spriteBatch.DrawString(font, "Computer vs Computer", new Vector2(100, 200), Color.Green); }
				else { game.spriteBatch.DrawString(font, "Computer vs Computer", new Vector2(100, 200), Color.White); }
				if (selectedItem == 2) { game.spriteBatch.DrawString(font, "Exit", new Vector2(100, 250), Color.Green); }
				else { game.spriteBatch.DrawString(font, "Exit", new Vector2(100, 250), Color.White); }
			}
			else
			{
				if (selectedItem == 0) { game.spriteBatch.DrawString(font, "Client", new Vector2(100, 175), Color.Green); }
				else { game.spriteBatch.DrawString(font, "Client", new Vector2(100, 175), Color.White); }
				if (selectedItem == 1) { game.spriteBatch.DrawString(font, "Server", new Vector2(100, 225), Color.Green); }
				else { game.spriteBatch.DrawString(font, "Server", new Vector2(100, 225), Color.White); }
			}

			game.spriteBatch.End();

			base.Draw(gameTime);
		}
	}
}