using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Net;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace XNAFrontend.Components
{
	class ConnectInputField : ACommonComponent
	{
		public IPAddress IpAddress { get; private set; }
		public int Port { get; private set; }

		public bool IsValid
		{
			get
			{
				if (!_connectionString.Contains(':'))
					return false;

				string[] parts = _connectionString.Split(':');

				if (parts.Length != 2)
					return false;

				try
				{
					IpAddress = IPAddress.Parse(parts[0]);
					Port = ushort.Parse(parts[1]);
				}
				catch (FormatException)
				{
					return false;
				}

				return true;
			}
		}

		private Vector2 _position;
		private string _prefix;
		private string _connectionString;
		private SpriteFont _font;
		private KeyboardState _oldState;

		public ConnectInputField(KaroGame game, Vector2 position, string prefix) : base(game)
		{
			_position = position;
			_prefix = prefix;
			_connectionString = "";

			Port = -1;
		}

		protected override void LoadContent()
		{
			_font = Game.Content.Load<SpriteFont>("SpriteFont1");
			base.LoadContent();
		}

		private bool didPressKey(Keys key)
		{
			return Keyboard.GetState().IsKeyDown(key) && !_oldState.IsKeyDown(key);
		}

		public override void Update(GameTime gameTime)
		{
			KeyboardState keyboard = Keyboard.GetState();

			if (_oldState == null)
			{
				_oldState = keyboard;
				base.Update(gameTime);
				return;
			}

			KeyObject[] keys = {
				new KeyObject(Keys.D0, '0'),
				new KeyObject(Keys.D1, '1'),
				new KeyObject(Keys.D2, '2'),
				new KeyObject(Keys.D3, '3'),
				new KeyObject(Keys.D4, '4'),
				new KeyObject(Keys.D5, '5'),
				new KeyObject(Keys.D6, '6'),
				new KeyObject(Keys.D7, '7'),
				new KeyObject(Keys.D8, '8'),
				new KeyObject(Keys.D9, '9'),
				new KeyObject(Keys.OemPeriod, '.'),
				new KeyObject(Keys.OemSemicolon, ":")
			};

			foreach (KeyObject key in keys) {
				if (!didPressKey(key.Key)) {
					continue;
				}

				_connectionString += key.Character;
			}

			if (didPressKey(Keys.Back) && _connectionString.Length > 0)
			{
				_connectionString = _connectionString.Substring(0, _connectionString.Length - 1);
			}

			base.Update(gameTime);

			_oldState = keyboard;
		}

		public override void Draw(GameTime gameTime)
		{
			karoGame.spriteBatch.Begin();

			karoGame.spriteBatch.DrawString(_font, _prefix, _position, Color.White);

			Vector2 stringOffset = new Vector2(_font.MeasureString(_prefix).X, 0);
			karoGame.spriteBatch.DrawString(_font, _connectionString, _position + stringOffset, Color.White);

			karoGame.spriteBatch.End();
			base.Draw(gameTime);
		}

		private class KeyObject
		{
			public readonly Keys Key;
			public readonly string Character;

			public KeyObject(Keys key, char character)
			{
				Key = key;
				Character = character.ToString();
			}

			public KeyObject(Keys key, string character) 
			{
				Key = key;
				Character = character;
			}
		}
	}
}
