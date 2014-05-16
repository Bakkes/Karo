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
    public class CameraComponent : ACommonComponent
    {
        private Matrix OriginalView { get; set; }
        private Vector3 CameraPosition = new Vector3(500.0f, 400.0f, 1000.0f);
        private Vector3 CalculatePosition = new Vector3(500.0f, 400.0f, 1000.0f);
        public Matrix ViewMatrix { get; set; }
        public Matrix ProjectionMatrix { get; set; }
        public Vector3 Position
        {
            get
            {
                return CameraPosition;
            }
        }

        private Vector2 PreviousMousePosition;
        private Matrix RotationMatrix
        {
            get
            {
                return  Matrix.CreateRotationX((float)Math.Atan(Rotation.Y/CameraPosition.Z))
               * Matrix.CreateRotationY((float)Math.Atan(Rotation.X /CameraPosition.Z));
                
            }
        }
        Vector2 Rotation = new Vector2(MathHelper.PiOver2, -MathHelper.Pi / 10.0f);
        const float rotationSpeed = 0.3f;
        public void MoveCamera(Vector3 Change)
        {
            CameraPosition += Vector3.Transform( Change,RotationMatrix);
            Matrix Movement = Matrix.CreateTranslation(Change);
            ViewMatrix *= Movement;
        }
        public CameraComponent(KaroGame game)
            : base(game)
        {
            PreviousMousePosition = new Vector2(0, 0);
            // TODO: Construct any child components here
            
        }

        /// <summary>
        /// Allows the game component to perform any initialization it needs to before starting
        /// to run.  This is where it can query for any required services and load content.
        /// </summary>
        public override void Initialize()
        {
            // TODO: Add your initialization code here

            ViewMatrix = Matrix.CreateLookAt(CameraPosition, Vector3.Zero, Vector3.Up);
            OriginalView = Matrix.CreateLookAt(CameraPosition, Vector3.Zero, Vector3.Up);
            float aspectRatio = karoGame.graphics.GraphicsDevice.Viewport.AspectRatio;
            ProjectionMatrix = Matrix.CreatePerspectiveFieldOfView(MathHelper.ToRadians(40f), aspectRatio, 100f, 100000f);
            base.Initialize();
        }

        /// <summary>
        /// Allows the game component to update itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Update(GameTime gameTime)
        {
            float speed = (float)(1* gameTime.ElapsedGameTime.TotalMilliseconds);
         
            if (Keyboard.GetState().IsKeyDown(Keys.W))
            {
                MoveCamera(new Vector3(0,0,speed));
            }

            if (Keyboard.GetState().IsKeyDown(Keys.S))
            {
                MoveCamera(new Vector3(0,0,-speed));

            }

            if (Keyboard.GetState().IsKeyDown(Keys.A))
            {
                 MoveCamera(new Vector3(speed,0,0));
            }
            if (Keyboard.GetState().IsKeyDown(Keys.D))
            {

                MoveCamera(new Vector3(-speed,0,0));
            }
            Vector2 MousePosition = new Vector2(Mouse.GetState().X, Mouse.GetState().Y);
            if (MousePosition != PreviousMousePosition)
            {
                Rotation -= (MousePosition - PreviousMousePosition);
            
                PreviousMousePosition = MousePosition;

               
               
                
                ViewMatrix = RotationMatrix * OriginalView; 
                ViewMatrix *= Matrix.CreateTranslation(CameraPosition - CalculatePosition);

            }
            
            base.Update(gameTime);
        }
    }
}
