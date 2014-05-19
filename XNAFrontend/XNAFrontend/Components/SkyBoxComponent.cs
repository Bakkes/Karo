using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework;

namespace XNAFrontend.Components
{
    class SkyBoxComponent: ACommonComponent
    {
        public SkyBoxComponent(KaroGame game)
            : base(game) { }

        string assetName = "skybox2";
        TextureCube texture;
        Model skyBox;
        public CameraComponent CameraComponent { get; set; }
        private Effect skyBoxEffect;

        GraphicsDevice device
        {
            get
            {
                return karoGame.graphics.GraphicsDevice;
            }
        }



        protected override void LoadContent()
        {
          
            skyBox = karoGame.Content.Load<Model>("cube");
            texture =karoGame.Content.Load<TextureCube>("Islands");
            skyBoxEffect = karoGame.Content.Load<Effect>("SkyBox");

            base.LoadContent();
          
        }
        public override void Draw(Microsoft.Xna.Framework.GameTime gameTime)
        {

            foreach (EffectPass pass in skyBoxEffect.CurrentTechnique.Passes)
            {
                // Draw all of the components of the mesh, but we know the cube really
                // only has one mesh
                foreach (ModelMesh mesh in skyBox.Meshes)
                {
                    // Assign the appropriate values to each of the parameters
                    foreach (ModelMeshPart part in mesh.MeshParts)
                    {
                        part.Effect = skyBoxEffect;
                        part.Effect.Parameters["World"].SetValue(
                            Matrix.CreateScale(50) * Matrix.CreateTranslation(CameraComponent.Position));
                        part.Effect.Parameters["View"].SetValue(CameraComponent.ViewMatrix);
                        part.Effect.Parameters["Projection"].SetValue(CameraComponent.ProjectionMatrix);
                        part.Effect.Parameters["SkyBoxTexture"].SetValue(texture);
                        part.Effect.Parameters["CameraPosition"].SetValue(CameraComponent.Position);
                    }

                    // Draw the mesh with the skybox effect
                    mesh.Draw();
                }
            }
            base.Draw(gameTime);
        }
    }


}
