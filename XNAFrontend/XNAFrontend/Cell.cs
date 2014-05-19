using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using engine.wrapper;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using XNAFrontend.Components;

namespace XNAFrontend {
	class Cell {
		public Model Model { get; set; }
		private CellWrapper _cell;
		public CellWrapper CellWrapper {
			get{
				return _cell;
			}
			set {
			_position = new Vector2(
				(float)value.GetRelativePosition().X, 
				(float)value.GetRelativePosition().Y
			);
				_cell = value;
			} 
		}
		private Vector2 _position;
		public Vector2 Position { get { return _position; } set { _position = value; } }
		public CameraComponent CameraComponent;
		public void Render(){
			if(!(CellWrapper == null || CellWrapper.HasTile())){
				return;
			}
			Matrix[] transforms = new Matrix[Model.Bones.Count];
			Model.CopyAbsoluteBoneTransformsTo(transforms);
			foreach (ModelMesh mesh in Model.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = 
						transforms[mesh.ParentBone.Index] *
						Matrix.CreateTranslation(
							new Vector3(
								(float)(-300 * Position.Y), 
								0, 
								(float)(-300* Position.X)
								)
							);
					effect.View = CameraComponent.ViewMatrix;
					effect.Projection = CameraComponent.ProjectionMatrix;
				}
				mesh.Draw();
			}
		}

	}
}
