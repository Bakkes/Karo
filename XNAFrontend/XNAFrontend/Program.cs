using System;

namespace XNAFrontend
{
#if WINDOWS || XBOX
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		static void Main(string[] args)
		{
			using (KaroGame game = new KaroGame())
			{
				game.Run();
			}
		}
	}
#endif
}

