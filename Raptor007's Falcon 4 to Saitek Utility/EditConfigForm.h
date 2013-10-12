#pragma once
namespace Raptor007sFalcon4toSaitekUtility
{
	ref class EditConfigForm;
}

#ifndef FORM_DESIGNER
#include "Saitek.h"
#include "Device.h"
#endif

#include <cstdio>
#include <string>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Raptor007sFalcon4toSaitekUtility
{
	/// <summary>
	/// Summary for EditConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class EditConfigForm : public System::Windows::Forms::Form
	{
	public:
		EditConfigForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditConfigForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  SaveButton;
	public: System::Windows::Forms::TextBox^  ConfigText;
	private: 

	private: System::Windows::Forms::Button^  CancelButton;
	public: System::Windows::Forms::Button^  ApplyButton;
	private: 

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(EditConfigForm::typeid));
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->ConfigText = (gcnew System::Windows::Forms::TextBox());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->ApplyButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// SaveButton
			// 
			this->SaveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->SaveButton->Location = System::Drawing::Point(282, 377);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(90, 23);
			this->SaveButton->TabIndex = 0;
			this->SaveButton->Text = L"&Save && Close";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &EditConfigForm::SaveButton_Click);
			// 
			// ConfigText
			// 
			this->ConfigText->AcceptsReturn = true;
			this->ConfigText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigText->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ConfigText->Location = System::Drawing::Point(13, 13);
			this->ConfigText->Multiline = true;
			this->ConfigText->Name = L"ConfigText";
			this->ConfigText->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->ConfigText->Size = System::Drawing::Size(359, 358);
			this->ConfigText->TabIndex = 1;
			this->ConfigText->TextChanged += gcnew System::EventHandler(this, &EditConfigForm::ConfigText_TextChanged);
			this->ConfigText->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &EditConfigForm::ConfigText_KeyUp);
			// 
			// CancelButton
			// 
			this->CancelButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CancelButton->Location = System::Drawing::Point(158, 377);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(56, 23);
			this->CancelButton->TabIndex = 2;
			this->CancelButton->Text = L"&Close";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &EditConfigForm::CancelButton_Click);
			// 
			// ApplyButton
			// 
			this->ApplyButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->ApplyButton->Enabled = false;
			this->ApplyButton->Location = System::Drawing::Point(220, 377);
			this->ApplyButton->Name = L"ApplyButton";
			this->ApplyButton->Size = System::Drawing::Size(56, 23);
			this->ApplyButton->TabIndex = 3;
			this->ApplyButton->Text = L"&Apply";
			this->ApplyButton->UseVisualStyleBackColor = true;
			this->ApplyButton->Click += gcnew System::EventHandler(this, &EditConfigForm::ApplyButton_Click);
			// 
			// EditConfigForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(384, 412);
			this->Controls->Add(this->ApplyButton);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->ConfigText);
			this->Controls->Add(this->SaveButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"EditConfigForm";
			this->Text = L"Edit Config";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void SaveButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			ApplyButton_Click( sender, e );

			if( ! ApplyButton->Enabled )
				Close();
		}
private: System::Void CancelButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			Close();
		}
private: System::Void ApplyButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			// Get the config name from the titlebar.
			const char *name_ptr = (const char *) (System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( Text )).ToPointer();
			std::string name( name_ptr );
			System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( (void*) name_ptr ) );
			
			// Temporarily suspend all device updating while we change the config.
			Saitek::MainThread->DoDeviceUpdates = false;
			System::Threading::Thread::Sleep( 100 );
			
			// Save basic config parameters for this device type.
			Saitek::Configs[ name ]->Clear();
			Saitek::Configs[ name ]->Save();
			
			std::string filename = std::string("Configs\\") + name + std::string(".cfg");
			FILE *out = fopen( filename.c_str(), "at" );
			if( out )
			{
				// Save the contents of the textbox.
				for( int i = 0; i < ConfigText->Lines->Length; i ++ )
				{
					const char *line_ptr = (const char *) (System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( ConfigText->Lines[ i ] )).ToPointer();
					std::string line( line_ptr );
					System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( (void*) line_ptr ) );
					
					fprintf( out, "%s\n", line.c_str() );
				}
				
				fflush( out );
				fclose( out );
				
				// Reload config from file.
				Saitek::Configs[ name ]->Load();
				
				// Restore device updating.
				Saitek::MainThread->DoDeviceUpdates = true;
				
				ApplyButton->Enabled = false;
			}
			else
				System::Windows::Forms::MessageBox::Show( "Couldn't save: " + gcnew System::String(filename.c_str()), "Couldn't Save Settings", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error );
		}
private: System::Void ConfigText_TextChanged( System::Object ^sender, System::EventArgs ^e )
		{
			ApplyButton->Enabled = true;
		}
private: System::Void ConfigText_KeyUp( System::Object ^sender, System::Windows::Forms::KeyEventArgs ^e )
		{
			if( e->Control && e->KeyCode == Keys::A )
				ConfigText->SelectAll();
		}
};
}
