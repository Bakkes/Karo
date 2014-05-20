using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;

namespace XNAFrontend.Services
{
    interface ICamera
    {
		Vector3 Position { get; set; }
		Matrix Projection { get; set; }
		Matrix View { get; set; }
    }
}
