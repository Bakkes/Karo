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


namespace XNAFrontend.Components
{
    /// <summary>
    /// This is a game component that implements IUpdateable.
    /// </summary>
    public abstract class ACommonComponent : Microsoft.Xna.Framework.DrawableGameComponent
    {
        protected KaroGame karoGame { get; set; }

        public ACommonComponent(KaroGame game)
            : base(game)
        {
            karoGame = game;
            // TODO:  Construct any child components here
        }

        public override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);
        }

    }

}
