namespace XNAFrontend.Components
{
	/// <summary>
	/// Exposes a component that is only active while loading.
	/// </summary>
	public interface ILoadingComponent
	{
		bool Loading { get; }
		void Start();
		void Stop();
	}
}
