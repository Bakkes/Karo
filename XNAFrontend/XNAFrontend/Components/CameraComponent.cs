using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using XNAFrontend.Services;
using engine.wrapper;


namespace XNAFrontend.Components
{
    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public class CameraComponent : ACommonComponent
    {

		private new KaroGame Game { get { return (KaroGame)base.Game; } }

        public CameraComponent(KaroGame game) : base(game)
        {
        }

        /// <summary>
        /// Allows the game component to perform any initialization it needs to before starting
        /// to run.  This is where it can query for any required services and load content.
        /// </summary>
        public override void Initialize()
        {
            base.Initialize();
        }

        /// <summary>
        /// Allows the game component to update itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Update(GameTime gameTime)
        {
            base.Update(gameTime);
        }

		/// <summary>
		/// Gets the maximum width of the board
		/// Note: This does not have to be the tile count
		/// </summary>
		/// <returns>the maximum amount of used cells in the width</returns>
		private int GetMaxBoardWidth()
		{
			BoardWrapper board = Game.KaroGameManager.Board;
			int maxWidth = 0;
			for (int y = 0; y < 20; y++)
			{
				for (int x = 19; x >= 0; x--)
				{
					if (!board.GetRelativeCellAt(new Vector2DWrapper(x, y)).HasTile())
					{
						continue;
					}

					if (x > maxWidth) {
						maxWidth = x;
					}
				}
			}
			return maxWidth;
		}

		/// <summary>
		/// Gets the maximum of the board
		/// Note: This does not have to be the tile count
		/// </summary>
		/// <returns>the maximum amount of used cells in the height</returns>
		private int GetMaxBoardHeight()
		{
			BoardWrapper board = Game.KaroGameManager.Board;
			int maxHeight = 0;
			for (int x = 0; x < 20; x++)
			{
				for (int y = 19; y >= 0; y--)
				{
					if (!board.GetRelativeCellAt(new Vector2DWrapper(x, y)).HasTile())
					{
						continue;
					}

					if (y > maxHeight) {
						maxHeight = y;
					}
				}
			}
			return maxHeight;
		}

	}
}
