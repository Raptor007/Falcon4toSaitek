#include "stdafx.h"
#include "FIPBitmap.h"

FIPBitmap::FIPBitmap( void )
{
	// Set the initial buffer to white, because this will be easier than black for trouble-shooting.
	memset( Buffer, 255, 320*240*3 );

	// Allocate managed bitmap and graphics objects.
	Bmp = gcnew System::Drawing::Bitmap( 320, 240, System::Drawing::Imaging::PixelFormat::Format24bppRgb );
	Gfx = System::Drawing::Graphics::FromImage( Bmp.get() );

	// Configure options for nicer drawing.
	Gfx->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	Gfx->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::Bilinear;
}

System::Drawing::Graphics ^FIPBitmap::GetGraphics()
{
	// Return a managed pointer to the graphics.
	return Gfx.get();
}

unsigned char *FIPBitmap::GetBuffer( void )
{
	// Do the gcroot lookup now to avoid repeating it.
	System::Drawing::Bitmap ^Bmp = this->Bmp.get();

	// Lock the bitmap to a specific place in memory and get an IntPtr to its data.
	System::Drawing::Imaging::BitmapData ^bits = Bmp->LockBits( System::Drawing::Rectangle( 0, 0, 320, 240 ), System::Drawing::Imaging::ImageLockMode::ReadOnly, System::Drawing::Imaging::PixelFormat::Format24bppRgb );

	// Convert the IntPtr to a C unsigned char pointer.
	const unsigned char *bitmap_array = reinterpret_cast<const unsigned char*>( bits->Scan0.ToPointer() );

	// Copy the lines to the buffer, swapping Y values to fix FIP output.
	for( int y = 0; y < 240; y ++ )
		memcpy( Buffer + (239-y)*320*3, bitmap_array + y*320*3, 320*3 );

	// Unlock the bitmap so it can be edited again.
	Bmp->UnlockBits( bits );

	// Return a pointer to the buffer for use with the FIP.
	return Buffer;
}
