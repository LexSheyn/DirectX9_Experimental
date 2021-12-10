#ifndef MENU_H
#define MENU_H

#include "../RenderSystem/Drawable.h"

namespace dx9
{
	class Menu : public Drawable
	{
	public:

	// Constructors and Destructor:

		Menu( HWND phWnd, IDirect3DDevice9* pD3DDevice  );

		~Menu();

	// Functions:

		/// <summary>
		/// Test draw function, for now it contains all events handling and stuff.
		/// </summary>
		void Draw() override;
	};
}

#endif // MENU_H