using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	class MessageComponent : ACommonComponent
	{
		public string Message { get; set; }

		private SpriteFont _font;

		public MessageComponent(KaroGame game)
			: base(game)
		{
			Message = "";
		}

		public MessageComponent(KaroGame game, string message)
			: base(game)
		{
			Message = message;
		}

		protected override void LoadContent()
		{
			_font = karoGame.Content.Load<SpriteFont>("SpriteFont1");
			base.LoadContent();
		}

		public override void Update(GameTime gameTime)
		{
			if (Keyboard.GetState().IsKeyDown(Keys.Enter))
			{
				karoGame.Components.Remove(this);
				karoGame.Components.Add(new MenuComponent(karoGame));
			}
			base.Update(gameTime);
		}

		public override void Draw(Microsoft.Xna.Framework.GameTime gameTime)
		{
			karoGame.spriteBatch.Begin();

			string returnMessage = "Hit enter to return to the menu";
			Vector2 messageSize = _font.MeasureString(Message);
			Vector2 returnSize = _font.MeasureString(returnMessage);

			Vector2 viewportSize = new Vector2(karoGame.GraphicsDevice.Viewport.Width, karoGame.GraphicsDevice.Viewport.Height);

			Vector2 centeredLocation = viewportSize / 2;

			karoGame.spriteBatch.DrawString(_font, Message, centeredLocation - (messageSize / 2), Color.White);
			karoGame.spriteBatch.DrawString(_font, returnMessage, centeredLocation - new Vector2(returnSize.X / 2, -5), Color.Green);
			karoGame.spriteBatch.End();

			base.Draw(gameTime);
		}
	}
}
