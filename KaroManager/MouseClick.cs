using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace KaroManager
{
	public enum MouseButton 
	{
		LEFT,
		RIGHT,
		MIDDLE
	}
	public class MouseClick
	{
		public Point Position { get; private set; }
		public MouseButton Button { get; private set; }

		public MouseClick(Point position, MouseButton button)
		{
			Position = position;
			Button = button;
		}
	}
}
