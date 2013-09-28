#pragma once
namespace Raptor007sFalcon4toSaitekUtility
{
	ref class NewConfigForm;
}

#ifndef FORM_DESIGNER
#include "Saitek.h"
#include "Device.h"
#include "X52Pro.h"
#include "FIP.h"
#endif

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Raptor007sFalcon4toSaitekUtility
{
	/// <summary>
	/// Summary for NewConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class NewConfigForm : public System::Windows::Forms::Form
	{
	public:
		NewConfigForm(void)
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
		~NewConfigForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  DeviceType;
	private: System::Windows::Forms::Label^  DeviceTypeLabel;
	private: System::Windows::Forms::TextBox^  ConfigName;
	private: System::Windows::Forms::Label^  ConfigNameLabel;
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::Button^  CancelButton;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(NewConfigForm::typeid));
			this->DeviceType = (gcnew System::Windows::Forms::ComboBox());
			this->DeviceTypeLabel = (gcnew System::Windows::Forms::Label());
			this->ConfigName = (gcnew System::Windows::Forms::TextBox());
			this->ConfigNameLabel = (gcnew System::Windows::Forms::Label());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// DeviceType
			// 
			this->DeviceType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DeviceType->FormattingEnabled = true;
			this->DeviceType->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"X52 Pro", L"FIP"});
			this->DeviceType->Location = System::Drawing::Point(89, 12);
			this->DeviceType->Name = L"DeviceType";
			this->DeviceType->Size = System::Drawing::Size(76, 21);
			this->DeviceType->TabIndex = 1;
			this->DeviceType->SelectedIndexChanged += gcnew System::EventHandler(this, &NewConfigForm::DeviceType_SelectedIndexChanged);
			// 
			// DeviceTypeLabel
			// 
			this->DeviceTypeLabel->AutoSize = true;
			this->DeviceTypeLabel->Location = System::Drawing::Point(12, 15);
			this->DeviceTypeLabel->Name = L"DeviceTypeLabel";
			this->DeviceTypeLabel->Size = System::Drawing::Size(71, 13);
			this->DeviceTypeLabel->TabIndex = 0;
			this->DeviceTypeLabel->Text = L"Device Type:";
			// 
			// ConfigName
			// 
			this->ConfigName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigName->Location = System::Drawing::Point(89, 39);
			this->ConfigName->Name = L"ConfigName";
			this->ConfigName->Size = System::Drawing::Size(190, 20);
			this->ConfigName->TabIndex = 3;
			this->ConfigName->TextChanged += gcnew System::EventHandler(this, &NewConfigForm::ConfigName_TextChanged);
			// 
			// ConfigNameLabel
			// 
			this->ConfigNameLabel->AutoSize = true;
			this->ConfigNameLabel->Location = System::Drawing::Point(12, 42);
			this->ConfigNameLabel->Name = L"ConfigNameLabel";
			this->ConfigNameLabel->Size = System::Drawing::Size(71, 13);
			this->ConfigNameLabel->TabIndex = 2;
			this->ConfigNameLabel->Text = L"Config Name:";
			// 
			// OKButton
			// 
			this->OKButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->OKButton->Enabled = false;
			this->OKButton->Location = System::Drawing::Point(237, 68);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(42, 23);
			this->OKButton->TabIndex = 5;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &NewConfigForm::OKButton_Click);
			// 
			// CancelButton
			// 
			this->CancelButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CancelButton->Location = System::Drawing::Point(179, 68);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(52, 23);
			this->CancelButton->TabIndex = 4;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &NewConfigForm::CancelButton_Click);
			// 
			// NewConfigForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(291, 103);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->ConfigNameLabel);
			this->Controls->Add(this->ConfigName);
			this->Controls->Add(this->DeviceTypeLabel);
			this->Controls->Add(this->DeviceType);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"NewConfigForm";
			this->Text = L"New Config";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void CancelButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			Close();
		}
private: System::Void OKButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			DeviceConfig *config = NULL;
			
			// Generate a new config for the selected device type.
			if( DeviceType->SelectedIndex == 0 )
				config = new X52ProConfig();
			else if( DeviceType->SelectedIndex == 1 )
				config = new FIPConfig();
			
			if( config )
			{
				// Set the config name.
				const char *name_ptr = (const char *) (System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( ConfigName->Text )).ToPointer();
				config->Name = name_ptr;
				System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( (void*) name_ptr ) );
				
				// Save a basic empty config for this device, and add it to the global list of configs.
				config->Save();
				Saitek::Configs[ config->Name ] = config;
				Saitek::ConfigsChanged = true;
				
				// Switch to the editor view.
				config->ShowEditWindow();
				Close();
			}
		}
private: System::Void DeviceType_SelectedIndexChanged ( System::Object ^sender, System::EventArgs ^e )
		{
			// Only enable OKButton if there's a device and config name entered (without slashes).
			if( (DeviceType->SelectedIndex >= 0) && (ConfigName->Text->Length > 0) && (! ConfigName->Text->Contains("/")) && (! ConfigName->Text->Contains("\\")) && (! ConfigName->Text->Contains("\"")) )
			{
				const char *name_ptr = (const char *) (System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( ConfigName->Text )).ToPointer();
				
				// Don't enable OKButton if the config name is already in use.
				OKButton->Enabled = (Saitek::Configs.find( std::string(name_ptr) ) == Saitek::Configs.end());
				
				System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( (void*) name_ptr ) );
			}
			else
				OKButton->Enabled = false;
		}
private: System::Void ConfigName_TextChanged( System::Object ^sender, System::EventArgs ^e )
		{
			DeviceType_SelectedIndexChanged( sender, e );
		}
};
}
