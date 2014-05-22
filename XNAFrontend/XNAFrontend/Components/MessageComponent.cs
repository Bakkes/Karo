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
		/// <summary>
		/// The message which is being show
		/// </summary>
		public string Message { get; set; }
		/// <summary>
		/// The message which explains what the enter key will do
		/// </summary>
		public string EnterMessage { get; set; }
		/// <summary>
		/// The Component to which we will go when the enter key gets hit
		/// </summary>
		public ACommonComponent EnterComponent { get; set; }

		private SpriteFont _font;

		public MessageComponent(KaroGame game)
			: base(game)
		{
			Message = "";
		}

		public MessageComponent(KaroGame game, string message, string enterMessage, ACommonComponent enterComponent)
			: base(game)
		{
			Message = message;
			EnterMessage = enterMessage;
			EnterComponent = enterComponent;
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

			Vector2 messageSize = _font.MeasureString(Message);
			Vector2 returnSize = _font.MeasureString(EnterMessage);

			Vector2 viewportSize = new Vector2(karoGame.GraphicsDevice.Viewport.Width, karoGame.GraphicsDevice.Viewport.Height);

			Vector2 centeredLocation = viewportSize / 2;

			karoGame.spriteBatch.DrawString(_font, Message, centeredLocation - (messageSize / 2), Color.White);
			karoGame.spriteBatch.DrawString(_font, EnterMessage, centeredLocation - new Vector2(returnSize.X / 2, -5), Color.Green);
			karoGame.spriteBatch.End();

			base.Draw(gameTime);
		}
	}
}
