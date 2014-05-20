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
using System.Diagnostics;

namespace XNAFrontend.Components
{
    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public class CameraComponent : ACommonComponent
    {
		/// <summary>
		/// The amount of units the camera can move in a second
		/// </summary>
		private const float CAMERA_MOVESPEED = 1f;

		private new KaroGame Game { get { return (KaroGame)base.Game; } }
		private ICamera Camera
		{
			get
			{
				return (ICamera)Game.Services.GetService(typeof(ICamera));
			}
		}

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
			int maxWidth = GetMaxBoardWidth();
			int maxHeight = GetMaxBoardWidth();

			Vector3 desiredPosition = new Vector3(maxWidth * Board.TOTAL_SPACING / 2, Camera.Position.Y, maxHeight * Board.TOTAL_SPACING / 2);
			Vector3 positionDifference = desiredPosition - Camera.Position;
			if (positionDifference.LengthSquared() != 0)
			{
				if (positionDifference.Length() > 1)
				{
					positionDifference.Normalize();
				}
				positionDifference *= (float)(CAMERA_MOVESPEED * (gameTime.ElapsedGameTime.TotalMilliseconds / 1000));
				Camera.Position += positionDifference;
			}

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
