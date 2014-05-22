using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Components
{
	class ConnectComponent : ACommonComponent
	{
		private ConnectInputField _inputField;
		private SpriteFont _font;

		public ConnectComponent(KaroGame game)
			: base(game)
		{
			_inputField = new ConnectInputField(game, new Vector2(100, 100), "Host: ");

			Game.Components.Add(_inputField);
		}

		protected override void LoadContent()
		{
			_font = Game.Content.Load<SpriteFont>("SpriteFont1");
			base.LoadContent();
		}

		public override void Draw(Microsoft.Xna.Framework.GameTime gameTime)
		{
			base.Draw(gameTime);
		}

		public void Dispose()
		{
			Game.Components.Remove(this);
			Game.Components.Remove(_inputField);
		}
	}
}
