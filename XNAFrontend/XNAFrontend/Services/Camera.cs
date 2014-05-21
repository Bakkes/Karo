using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace XNAFrontend.Services
{
	class Camera : ICamera
	{
		public Matrix Projection { get; set; }
		public Matrix View { get; set; }
	}
}
