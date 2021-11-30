#ifndef D3DUTILITY_H
#define D3DUTILITY_H

namespace dx9
{
	template <class T> void Release( T t )
	{
		if ( t )
		{
			t->Release();

			t = nullptr;
		}
	}

	template <class T> void Delete( T t )
	{
		if ( t )
		{
			delete t;

			t = nullptr;
		}
	}
}

#endif // D3DUTILITY_H