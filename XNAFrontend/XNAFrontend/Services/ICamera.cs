using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;

namespace XNAFrontend.Services
{
    interface ICamera
    {
		Vector3 Position { get; }
		Matrix Projection { get; }
		Matrix View { get; }
    }
}
