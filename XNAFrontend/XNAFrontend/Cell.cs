using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using engine.wrapper;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using XNAFrontend.Components;
using XNAFrontend.Services;

namespace XNAFrontend {
	class Cell {
		public Model Model { get; set; }
		private CellWrapper _cell;
		public GameServiceContainer Services { get; set; }
		public CellWrapper CellWrapper {
			get{
				return _cell;
			}
			set {
			_position = new Vector2(
				(float)value.GetAbsolutePosition().X, 
				(float)value.GetAbsolutePosition().Y
			);
				_cell = value;
			} 
		}
		private Vector2 _position;
		public Vector2 Position { get { return _position; } set { _position = value; } }

		private ICamera Camera{
			get{
				
				return(ICamera)Services.GetService(typeof(ICamera));
			}
		}
		public void Render(){
			if(!(CellWrapper == null || CellWrapper.HasTile())){
				return;
			}
			Matrix world = Matrix.CreateRotationX(MathHelper.ToRadians(-90));
			foreach (ModelMesh mesh in Model.Meshes)
			{
				foreach (BasicEffect effect in mesh.Effects)
				{
					effect.EnableDefaultLighting();
					effect.World = 
						world*
						Matrix.CreateTranslation(
							new Vector3(
								(float)Position.X,
								0, 
								(float)Position.Y
								)
							);
					effect.View = Camera.View;
					effect.Projection = Camera.Projection;
				}
				mesh.Draw();
			}
		}

	}
}
