#pragma once
namespace Raptor007sFalcon4toSaitekUtility
{
	ref class MainForm;
}

#ifndef FORM_DESIGNER
#include "Saitek.h"
#include "NewConfigForm.h"
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
	/// Summary for MainForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::GroupBox^  InstanceGroup;
	private: System::Windows::Forms::GroupBox^  ConfigGroup;
	private: System::Windows::Forms::GroupBox^  FalconGroup;
	private: System::Windows::Forms::Button^  StartButton;
	private: System::Windows::Forms::Button^  RestartServiceButton;
	private: System::Windows::Forms::ListBox^  InstanceListBox;
	private: System::Windows::Forms::ListBox^  ConfigListBox;
	private: System::Windows::Forms::Label^  DeviceText;
	private: System::Windows::Forms::PictureBox^  DeviceImage;
	private: System::Windows::Forms::TextBox^  GuidText;
	private: System::Windows::Forms::LinkLabel^  ForumLink;
	private: System::Windows::Forms::CheckBox^  WaitForFalcon;
	private: System::Windows::Forms::Button^  EditConfigButton;
	private: System::Windows::Forms::ComboBox^  FalconType;
	private: System::Windows::Forms::CheckBox^  AutoLaunch;
	private: System::Windows::Forms::TextBox^  FalconPath;
	private: System::Windows::Forms::ComboBox^  SelectedConfig;
	private: System::Windows::Forms::Button^  FalconBrowseButton;
	private: System::Windows::Forms::Label^  FalconParametersLabel;
	private: System::Windows::Forms::TextBox^  FalconParameters;
	private: System::Windows::Forms::Label^  ConfigName;
	private: System::Windows::Forms::Label^  ConfigType;
	private: System::Windows::Forms::PictureBox^  ConfigImage;
	private: System::Windows::Forms::Button^  NewConfigButton;
	private: System::Windows::Forms::Button^  DeleteConfigButton;




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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->InstanceGroup = (gcnew System::Windows::Forms::GroupBox());
			this->SelectedConfig = (gcnew System::Windows::Forms::ComboBox());
			this->GuidText = (gcnew System::Windows::Forms::TextBox());
			this->DeviceImage = (gcnew System::Windows::Forms::PictureBox());
			this->DeviceText = (gcnew System::Windows::Forms::Label());
			this->InstanceListBox = (gcnew System::Windows::Forms::ListBox());
			this->ConfigGroup = (gcnew System::Windows::Forms::GroupBox());
			this->DeleteConfigButton = (gcnew System::Windows::Forms::Button());
			this->NewConfigButton = (gcnew System::Windows::Forms::Button());
			this->ConfigImage = (gcnew System::Windows::Forms::PictureBox());
			this->ConfigType = (gcnew System::Windows::Forms::Label());
			this->ConfigName = (gcnew System::Windows::Forms::Label());
			this->EditConfigButton = (gcnew System::Windows::Forms::Button());
			this->ConfigListBox = (gcnew System::Windows::Forms::ListBox());
			this->FalconGroup = (gcnew System::Windows::Forms::GroupBox());
			this->FalconBrowseButton = (gcnew System::Windows::Forms::Button());
			this->FalconParametersLabel = (gcnew System::Windows::Forms::Label());
			this->FalconParameters = (gcnew System::Windows::Forms::TextBox());
			this->FalconPath = (gcnew System::Windows::Forms::TextBox());
			this->AutoLaunch = (gcnew System::Windows::Forms::CheckBox());
			this->FalconType = (gcnew System::Windows::Forms::ComboBox());
			this->WaitForFalcon = (gcnew System::Windows::Forms::CheckBox());
			this->StartButton = (gcnew System::Windows::Forms::Button());
			this->RestartServiceButton = (gcnew System::Windows::Forms::Button());
			this->ForumLink = (gcnew System::Windows::Forms::LinkLabel());
			this->InstanceGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DeviceImage))->BeginInit();
			this->ConfigGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ConfigImage))->BeginInit();
			this->FalconGroup->SuspendLayout();
			this->SuspendLayout();
			// 
			// InstanceGroup
			// 
			this->InstanceGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->InstanceGroup->Controls->Add(this->SelectedConfig);
			this->InstanceGroup->Controls->Add(this->GuidText);
			this->InstanceGroup->Controls->Add(this->DeviceImage);
			this->InstanceGroup->Controls->Add(this->DeviceText);
			this->InstanceGroup->Controls->Add(this->InstanceListBox);
			this->InstanceGroup->Location = System::Drawing::Point(13, 13);
			this->InstanceGroup->Name = L"InstanceGroup";
			this->InstanceGroup->Size = System::Drawing::Size(301, 243);
			this->InstanceGroup->TabIndex = 0;
			this->InstanceGroup->TabStop = false;
			this->InstanceGroup->Text = L"Detected Devices:";
			// 
			// SelectedConfig
			// 
			this->SelectedConfig->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->SelectedConfig->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectedConfig->Enabled = false;
			this->SelectedConfig->FormattingEnabled = true;
			this->SelectedConfig->Location = System::Drawing::Point(80, 216);
			this->SelectedConfig->Name = L"SelectedConfig";
			this->SelectedConfig->Size = System::Drawing::Size(215, 21);
			this->SelectedConfig->TabIndex = 5;
			this->SelectedConfig->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::SelectedConfig_SelectedIndexChanged);
			// 
			// GuidText
			// 
			this->GuidText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->GuidText->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->GuidText->Location = System::Drawing::Point(77, 189);
			this->GuidText->Name = L"GuidText";
			this->GuidText->ReadOnly = true;
			this->GuidText->Size = System::Drawing::Size(218, 13);
			this->GuidText->TabIndex = 4;
			// 
			// DeviceImage
			// 
			this->DeviceImage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->DeviceImage->Location = System::Drawing::Point(7, 173);
			this->DeviceImage->Name = L"DeviceImage";
			this->DeviceImage->Size = System::Drawing::Size(64, 64);
			this->DeviceImage->TabIndex = 1;
			this->DeviceImage->TabStop = false;
			// 
			// DeviceText
			// 
			this->DeviceText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->DeviceText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->DeviceText->Location = System::Drawing::Point(77, 173);
			this->DeviceText->Name = L"DeviceText";
			this->DeviceText->Size = System::Drawing::Size(218, 13);
			this->DeviceText->TabIndex = 2;
			// 
			// InstanceListBox
			// 
			this->InstanceListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->InstanceListBox->FormattingEnabled = true;
			this->InstanceListBox->Location = System::Drawing::Point(7, 20);
			this->InstanceListBox->Name = L"InstanceListBox";
			this->InstanceListBox->ScrollAlwaysVisible = true;
			this->InstanceListBox->Size = System::Drawing::Size(288, 147);
			this->InstanceListBox->TabIndex = 0;
			this->InstanceListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::InstanceListBox_SelectedIndexChanged);
			this->InstanceListBox->MouseEnter += gcnew System::EventHandler(this, &MainForm::InstanceListBox_Update);
			// 
			// ConfigGroup
			// 
			this->ConfigGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigGroup->Controls->Add(this->DeleteConfigButton);
			this->ConfigGroup->Controls->Add(this->NewConfigButton);
			this->ConfigGroup->Controls->Add(this->ConfigImage);
			this->ConfigGroup->Controls->Add(this->ConfigType);
			this->ConfigGroup->Controls->Add(this->ConfigName);
			this->ConfigGroup->Controls->Add(this->EditConfigButton);
			this->ConfigGroup->Controls->Add(this->ConfigListBox);
			this->ConfigGroup->Location = System::Drawing::Point(320, 13);
			this->ConfigGroup->Name = L"ConfigGroup";
			this->ConfigGroup->Size = System::Drawing::Size(292, 243);
			this->ConfigGroup->TabIndex = 1;
			this->ConfigGroup->TabStop = false;
			this->ConfigGroup->Text = L"Configurations:";
			// 
			// DeleteConfigButton
			// 
			this->DeleteConfigButton->Enabled = false;
			this->DeleteConfigButton->Location = System::Drawing::Point(235, 214);
			this->DeleteConfigButton->Name = L"DeleteConfigButton";
			this->DeleteConfigButton->Size = System::Drawing::Size(50, 23);
			this->DeleteConfigButton->TabIndex = 6;
			this->DeleteConfigButton->Text = L"&Delete";
			this->DeleteConfigButton->UseVisualStyleBackColor = true;
			this->DeleteConfigButton->Click += gcnew System::EventHandler(this, &MainForm::DeleteConfigButton_Click);
			// 
			// NewConfigButton
			// 
			this->NewConfigButton->Location = System::Drawing::Point(123, 214);
			this->NewConfigButton->Name = L"NewConfigButton";
			this->NewConfigButton->Size = System::Drawing::Size(50, 23);
			this->NewConfigButton->TabIndex = 4;
			this->NewConfigButton->Text = L"&New";
			this->NewConfigButton->UseVisualStyleBackColor = true;
			this->NewConfigButton->Click += gcnew System::EventHandler(this, &MainForm::NewConfigButton_Click);
			// 
			// ConfigImage
			// 
			this->ConfigImage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ConfigImage->Location = System::Drawing::Point(7, 172);
			this->ConfigImage->Name = L"ConfigImage";
			this->ConfigImage->Size = System::Drawing::Size(64, 64);
			this->ConfigImage->TabIndex = 1;
			this->ConfigImage->TabStop = false;
			// 
			// ConfigType
			// 
			this->ConfigType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigType->Location = System::Drawing::Point(77, 189);
			this->ConfigType->Name = L"ConfigType";
			this->ConfigType->Size = System::Drawing::Size(209, 13);
			this->ConfigType->TabIndex = 3;
			// 
			// ConfigName
			// 
			this->ConfigName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ConfigName->Location = System::Drawing::Point(77, 172);
			this->ConfigName->Name = L"ConfigName";
			this->ConfigName->Size = System::Drawing::Size(209, 13);
			this->ConfigName->TabIndex = 2;
			// 
			// EditConfigButton
			// 
			this->EditConfigButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->EditConfigButton->Enabled = false;
			this->EditConfigButton->Location = System::Drawing::Point(179, 214);
			this->EditConfigButton->Name = L"EditConfigButton";
			this->EditConfigButton->Size = System::Drawing::Size(50, 23);
			this->EditConfigButton->TabIndex = 5;
			this->EditConfigButton->Text = L"&Edit";
			this->EditConfigButton->UseVisualStyleBackColor = true;
			this->EditConfigButton->Click += gcnew System::EventHandler(this, &MainForm::EditConfigButton_Click);
			// 
			// ConfigListBox
			// 
			this->ConfigListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ConfigListBox->FormattingEnabled = true;
			this->ConfigListBox->Location = System::Drawing::Point(7, 20);
			this->ConfigListBox->Name = L"ConfigListBox";
			this->ConfigListBox->ScrollAlwaysVisible = true;
			this->ConfigListBox->Size = System::Drawing::Size(279, 147);
			this->ConfigListBox->TabIndex = 0;
			this->ConfigListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ConfigListBox_SelectedIndexChanged);
			this->ConfigListBox->MouseEnter += gcnew System::EventHandler(this, &MainForm::ConfigListBox_Update);
			// 
			// FalconGroup
			// 
			this->FalconGroup->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->FalconGroup->Controls->Add(this->FalconBrowseButton);
			this->FalconGroup->Controls->Add(this->FalconParametersLabel);
			this->FalconGroup->Controls->Add(this->FalconParameters);
			this->FalconGroup->Controls->Add(this->FalconPath);
			this->FalconGroup->Controls->Add(this->AutoLaunch);
			this->FalconGroup->Controls->Add(this->FalconType);
			this->FalconGroup->Controls->Add(this->WaitForFalcon);
			this->FalconGroup->Location = System::Drawing::Point(13, 262);
			this->FalconGroup->Name = L"FalconGroup";
			this->FalconGroup->Size = System::Drawing::Size(598, 139);
			this->FalconGroup->TabIndex = 2;
			this->FalconGroup->TabStop = false;
			this->FalconGroup->Text = L"Falcon:";
			// 
			// FalconBrowseButton
			// 
			this->FalconBrowseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->FalconBrowseButton->Enabled = false;
			this->FalconBrowseButton->Location = System::Drawing::Point(517, 105);
			this->FalconBrowseButton->Name = L"FalconBrowseButton";
			this->FalconBrowseButton->Size = System::Drawing::Size(75, 23);
			this->FalconBrowseButton->TabIndex = 6;
			this->FalconBrowseButton->Text = L"&Browse...";
			this->FalconBrowseButton->UseVisualStyleBackColor = true;
			this->FalconBrowseButton->Click += gcnew System::EventHandler(this, &MainForm::FalconBrowseButton_Click);
			// 
			// FalconParametersLabel
			// 
			this->FalconParametersLabel->AutoSize = true;
			this->FalconParametersLabel->Enabled = false;
			this->FalconParametersLabel->Location = System::Drawing::Point(19, 110);
			this->FalconParametersLabel->Name = L"FalconParametersLabel";
			this->FalconParametersLabel->Size = System::Drawing::Size(136, 13);
			this->FalconParametersLabel->TabIndex = 4;
			this->FalconParametersLabel->Text = L"Command-Line Parameters:";
			// 
			// FalconParameters
			// 
			this->FalconParameters->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->FalconParameters->Enabled = false;
			this->FalconParameters->Location = System::Drawing::Point(155, 107);
			this->FalconParameters->Name = L"FalconParameters";
			this->FalconParameters->Size = System::Drawing::Size(356, 20);
			this->FalconParameters->TabIndex = 5;
			this->FalconParameters->TextChanged += gcnew System::EventHandler(this, &MainForm::FalconParameters_TextChanged);
			// 
			// FalconPath
			// 
			this->FalconPath->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->FalconPath->Enabled = false;
			this->FalconPath->Location = System::Drawing::Point(155, 81);
			this->FalconPath->Name = L"FalconPath";
			this->FalconPath->Size = System::Drawing::Size(437, 20);
			this->FalconPath->TabIndex = 3;
			this->FalconPath->TextChanged += gcnew System::EventHandler(this, &MainForm::FalconPath_TextChanged);
			// 
			// AutoLaunch
			// 
			this->AutoLaunch->AutoSize = true;
			this->AutoLaunch->Location = System::Drawing::Point(7, 83);
			this->AutoLaunch->Name = L"AutoLaunch";
			this->AutoLaunch->Size = System::Drawing::Size(151, 17);
			this->AutoLaunch->TabIndex = 2;
			this->AutoLaunch->Text = L"&Automatically Start Falcon:";
			this->AutoLaunch->UseVisualStyleBackColor = true;
			this->AutoLaunch->CheckedChanged += gcnew System::EventHandler(this, &MainForm::AutoLaunch_CheckedChanged);
			// 
			// FalconType
			// 
			this->FalconType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FalconType->FormattingEnabled = true;
			this->FalconType->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"Allied Force", L"BMS2 / FreeFalcon4 / RedViper", 
				L"BMS3", L"BMS4", L"OpenFalcon", L"FreeFalcon5"});
			this->FalconType->Location = System::Drawing::Point(6, 19);
			this->FalconType->Name = L"FalconType";
			this->FalconType->Size = System::Drawing::Size(172, 21);
			this->FalconType->TabIndex = 0;
			this->FalconType->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::FalconType_SelectedIndexChanged);
			// 
			// WaitForFalcon
			// 
			this->WaitForFalcon->AutoSize = true;
			this->WaitForFalcon->Location = System::Drawing::Point(7, 46);
			this->WaitForFalcon->Name = L"WaitForFalcon";
			this->WaitForFalcon->Size = System::Drawing::Size(461, 30);
			this->WaitForFalcon->TabIndex = 1;
			this->WaitForFalcon->Text = L"&Wait for Falcon\r\nAfter clicking Start, nothing will happen on your Saitek device" 
				L"s until after Falcon is launched.";
			this->WaitForFalcon->UseVisualStyleBackColor = true;
			this->WaitForFalcon->CheckedChanged += gcnew System::EventHandler(this, &MainForm::WaitForFalcon_CheckedChanged);
			// 
			// StartButton
			// 
			this->StartButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->StartButton->Location = System::Drawing::Point(536, 407);
			this->StartButton->Name = L"StartButton";
			this->StartButton->Size = System::Drawing::Size(75, 23);
			this->StartButton->TabIndex = 5;
			this->StartButton->Text = L"&Start";
			this->StartButton->UseVisualStyleBackColor = true;
			this->StartButton->Click += gcnew System::EventHandler(this, &MainForm::StartButton_Click);
			// 
			// RestartServiceButton
			// 
			this->RestartServiceButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->RestartServiceButton->Location = System::Drawing::Point(13, 407);
			this->RestartServiceButton->Name = L"RestartServiceButton";
			this->RestartServiceButton->Size = System::Drawing::Size(129, 23);
			this->RestartServiceButton->TabIndex = 3;
			this->RestartServiceButton->Text = L"&Restart DirectOutput";
			this->RestartServiceButton->UseVisualStyleBackColor = true;
			this->RestartServiceButton->Click += gcnew System::EventHandler(this, &MainForm::RestartServiceButton_Click);
			// 
			// ForumLink
			// 
			this->ForumLink->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->ForumLink->Location = System::Drawing::Point(148, 412);
			this->ForumLink->Name = L"ForumLink";
			this->ForumLink->Size = System::Drawing::Size(382, 13);
			this->ForumLink->TabIndex = 4;
			this->ForumLink->TabStop = true;
			this->ForumLink->Text = L"Check for Updates at Raptor007.com";
			this->ForumLink->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ForumLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::ForumLink_LinkClicked);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 442);
			this->Controls->Add(this->ForumLink);
			this->Controls->Add(this->RestartServiceButton);
			this->Controls->Add(this->StartButton);
			this->Controls->Add(this->FalconGroup);
			this->Controls->Add(this->ConfigGroup);
			this->Controls->Add(this->InstanceGroup);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"Raptor007\'s Falcon 4 to Saitek Utility 2.1";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->InstanceGroup->ResumeLayout(false);
			this->InstanceGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DeviceImage))->EndInit();
			this->ConfigGroup->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ConfigImage))->EndInit();
			this->FalconGroup->ResumeLayout(false);
			this->FalconGroup->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void MainForm_Load( System::Object ^sender, System::EventArgs ^e )
		{
			// Populate the keymap (key names to scancodes).
			Saitek::InitKeyMap();
			
			// Select AlliedForce by default.
			try
			{
				System::String ^alliedforce_param = Saitek::MainThread->Config.FalconParameters[ F4SharedMem::FalconDataFormats::AlliedForce ];
				FalconType->SelectedIndex = 0;
				Saitek::MainThread->Config.FalconParameters[ F4SharedMem::FalconDataFormats::AlliedForce ] = alliedforce_param;
			}
			catch( System::Collections::Generic::KeyNotFoundException^ )
			{
				FalconType->SelectedIndex = 0;
			}

			// Load all configs, including Falcon paths and selected type.
			Saitek::LoadConfigs();
			
			// Keep track of the actual selected type, but set the config variable to AlliedForce temporarily.
			F4SharedMem::FalconDataFormats falcon_type = Saitek::MainThread->Config.FalconType;
			Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
			
			// Read AlliedForce path and params into textboxes.
			try
			{
				FalconPath->Text = Saitek::MainThread->Config.FalconPaths[ F4SharedMem::FalconDataFormats::AlliedForce ];
			}
			catch( System::Collections::Generic::KeyNotFoundException^ ){}
			
			try
			{
				FalconParameters->Text = Saitek::MainThread->Config.FalconParameters[ F4SharedMem::FalconDataFormats::AlliedForce ];
			}
			catch( System::Collections::Generic::KeyNotFoundException^ ){}
			
			WaitForFalcon->Checked = Saitek::MainThread->Config.WaitForFalcon;
			AutoLaunch->Checked = Saitek::MainThread->Config.AutoLaunch;
			
			// Set dropdown to actual selected type.
			if( falcon_type == F4SharedMem::FalconDataFormats::AlliedForce )
				FalconType->SelectedIndex = 0;
			else if( falcon_type == F4SharedMem::FalconDataFormats::BMS2 )
				FalconType->SelectedIndex = 1;
			else if( falcon_type == F4SharedMem::FalconDataFormats::BMS3 )
				FalconType->SelectedIndex = 2;
			else if( falcon_type == F4SharedMem::FalconDataFormats::BMS4 )
				FalconType->SelectedIndex = 3;
			else if( falcon_type == F4SharedMem::FalconDataFormats::OpenFalcon )
				FalconType->SelectedIndex = 4;
			else if( falcon_type == F4SharedMem::FalconDataFormats::FreeFalcon5 )
				FalconType->SelectedIndex = 5;
			
			// Update list of configs.
			Saitek::ConfigsChanged = true;
			ConfigListBox_Update( sender, e );
			
			// Start talking to DirectOutput.
			Saitek::Initialize();
			
			// Assign configs.
			Saitek::InstancesLock->WaitOne();
			std::map< std::string, int > counts;
			for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
			{
				std::string guid = (*inst_iter)->GuidString();
				if( counts.find(guid) == counts.end() )
					counts[ guid ] = 0;
				
				try
				{
					System::String ^guid_str = gcnew System::String( guid.c_str() );
					if( Saitek::MainThread->Config.StartupConfigs.ContainsKey(guid_str) && (counts[guid] < Saitek::MainThread->Config.StartupConfigs[guid_str]->Count) )
					{
						System::String ^config_name_str = Saitek::MainThread->Config.StartupConfigs[ guid_str ][ counts[guid] ];
						if( config_name_str->Length )
						{
							// There was a config selected for this device, so find it and select it.
							char *config_name_ptr = (char*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( config_name_str ).ToPointer();
							std::string config_name( config_name_ptr );
							System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( config_name_ptr ) );
							std::map<std::string, DeviceConfig*>::iterator config_iter = Saitek::Configs.find( config_name );
							if( config_iter != Saitek::Configs.end() )
								(*inst_iter)->Config = config_iter->second;
						}
						else
							// This device was disabled intentionally, so unselect the config.
							(*inst_iter)->Config = NULL;
					}
					delete guid_str;
				}
				catch( ... ){}
				
				counts[ guid ] ++;
			}
			Saitek::InstancesLock->ReleaseMutex();
			
			// Update form.
			InstanceListBox_Update( sender, e );
			InstanceListBox_SelectedIndexChanged( sender, e );
			ConfigListBox_SelectedIndexChanged( sender, e );
		}
private: System::Void StartButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			if( Saitek::MainThread->Running )
			{
				Saitek::MainThread->Running = false;
				StartButton->Text = "Stopping...";
				StartButton->Enabled = false;
				while( Saitek::MainThread->ChildThreads );
				System::GC::Collect();
				StartButton->Text = "Start";
				StartButton->Enabled = true;
				
				RestartServiceButton->Enabled = true;
				FalconType->Enabled = true;
				AutoLaunch->Enabled = true;
				AutoLaunch_CheckedChanged( sender, e );
				DeleteConfigButton->Enabled = EditConfigButton->Enabled;
			}
			else if( Saitek::Instances.size() )
			{
				if( AutoLaunch->Checked && (FalconPath->Text->Length <= 0) )
				{
					while( FalconPath->Text->Length <= 0 )
					{
						System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show( "You did not specify a Falcon 4 executable.\nWould you like to find it now?", "Falcon 4 Exe Not Selected", System::Windows::Forms::MessageBoxButtons::YesNoCancel, System::Windows::Forms::MessageBoxIcon::Question );
						if( result == System::Windows::Forms::DialogResult::Cancel )
							return;
						if( result == System::Windows::Forms::DialogResult::No )
							break;
						FalconBrowseButton_Click( sender, e );
					}
				}
				
				RestartServiceButton->Enabled = false;
				FalconType->Enabled = false;
				AutoLaunch->Enabled = false;
				FalconPath->Enabled = false;
				FalconBrowseButton->Enabled = false;
				FalconParameters->Enabled = false;
				FalconParametersLabel->Enabled = false;
				DeleteConfigButton->Enabled = false;
				
				StartButton->Text = "Starting...";
				StartButton->Enabled = false;
				System::Threading::ThreadStart ^thread_start = gcnew System::Threading::ThreadStart( Saitek::MainThread.get(), &(FalconThread::Code) );
				System::Threading::Thread ^thread = gcnew System::Threading::Thread( thread_start );
				thread->Start();
				delete thread_start;
				StartButton->Text = "Stop";
				StartButton->Enabled = true;
			}
			else
				MessageBox::Show( "No Saitek DirectOutput devices were detected!\nTry unplugging and then replugging them, running this utility as administrator, and/or renistalling the drivers.", "No Saitek DirectOutput Devices Detected", MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
		}
private: System::Void RestartServiceButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::RestartService();
		}
private: System::Void InstanceListBox_Update( System::Object ^sender, System::EventArgs ^e )
		{
			if( Saitek::InstancesChanged )
			{
				Saitek::InstancesLock->WaitOne();
				Saitek::InstancesChanged = false;
				
				int count_x52pro = 0;
				int count_fip = 0;
				int count_unknown = 0;
				
				InstanceListBox->Items->Clear();
				for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
				{
					if( (*inst_iter)->Guid == DeviceType_X52Pro )
					{
						count_x52pro ++;
						InstanceListBox->Items->Add( "X52 Pro #" + count_x52pro );
					}
					else if( (*inst_iter)->Guid == DeviceType_Fip )
					{
						count_fip ++;
						InstanceListBox->Items->Add( "FIP #" + count_fip );
					}
					else
					{
						count_unknown ++;
						InstanceListBox->Items->Add( "Unknown #" + count_unknown );
					}
				}
				
				Saitek::InstancesLock->ReleaseMutex();
			}
			
			SelectedConfig->Enabled = (InstanceListBox->SelectedIndex >= 0);
		}
private: System::Void InstanceListBox_SelectedIndexChanged( System::Object ^sender, System::EventArgs ^e )
		{
			DeviceText->Text = InstanceListBox->Text;
			
			DeviceInstance *dev_inst = NULL;
			GUID guid;
			DeviceConfig *config = NULL;
			
			Saitek::InstancesLock->WaitOne();
			
			try
			{
				dev_inst = Saitek::Instances.at( InstanceListBox->SelectedIndex );
				guid = dev_inst->Guid;
				config = dev_inst->Config;
				GuidText->Text = gcnew System::String( dev_inst->GuidString().c_str() );
				
				if( guid == DeviceType_X52Pro )
					DeviceImage->ImageLocation = "Images/icon_x52pro.png";
				else if( guid == DeviceType_Fip )
					DeviceImage->ImageLocation = "Images/icon_fip.png";
				else
					DeviceImage->ImageLocation = "Images/icon_unknown.png";
			}
			catch( std::out_of_range e )
			{
				DeviceText->Text = "(no device selected)";
				GuidText->Text = "";
				DeviceImage->ImageLocation = "Images/icon_unknown.png";
			}
			
			Saitek::InstancesLock->ReleaseMutex();
			
			SelectedConfig->Items->Clear();
			if( dev_inst )
			{
				SelectedConfig->Items->Add( "(disabled)" );
				for( std::map<std::string, DeviceConfig*>::iterator conf_iter = Saitek::Configs.begin(); conf_iter != Saitek::Configs.end(); conf_iter ++ )
				{
					if( conf_iter->second->Guid == guid )
						SelectedConfig->Items->Add( gcnew System::String(conf_iter->second->Name.c_str()) );
					
					if( config == conf_iter->second )
						SelectedConfig->SelectedIndex = SelectedConfig->Items->Count - 1;
				}
				
				if( ! config )
					SelectedConfig->SelectedIndex = 0;
			}
			
			SelectedConfig->Enabled = (InstanceListBox->SelectedIndex >= 0);
		}
private: System::Void ConfigListBox_Update( System::Object ^sender, System::EventArgs ^e )
		{
			if( Saitek::ConfigsChanged )
			{
				Saitek::ConfigsChanged = false;
				
				ConfigListBox->Items->Clear();
				for( std::map<std::string, DeviceConfig*>::iterator cfg_iter = Saitek::Configs.begin(); cfg_iter != Saitek::Configs.end(); cfg_iter ++ )
				{
					ConfigListBox->Items->Add( gcnew System::String(cfg_iter->second->Name.c_str()) );
				}
				
				InstanceListBox_SelectedIndexChanged( sender, e );
			}
		}
private: System::Void ForumLink_LinkClicked( System::Object ^sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^e )
		{
			System::Diagnostics::Process::Start( "http://www.raptor007.com/falcon-4-to-saitek/" );
		}
private: System::Void WaitForFalcon_CheckedChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::MainThread->Config.WaitForFalcon = WaitForFalcon->Checked;
		}
private: System::Void EditConfigButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			int index = 0;
			for( std::map<std::string, DeviceConfig*>::iterator cfg_iter = Saitek::Configs.begin(); cfg_iter != Saitek::Configs.end(); cfg_iter ++ )
			{
				if( index == ConfigListBox->SelectedIndex )
					cfg_iter->second->ShowEditWindow();
				index ++;
			}
		}
private: System::Void FalconType_SelectedIndexChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::MainThread->Config.FalconPaths[ Saitek::MainThread->Config.FalconType ] = FalconPath->Text;
			Saitek::MainThread->Config.FalconParameters[ Saitek::MainThread->Config.FalconType ] = FalconParameters->Text;
			
			if( FalconType->SelectedIndex == 0 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
			else if( FalconType->SelectedIndex == 1 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::BMS2;
			else if( FalconType->SelectedIndex == 2 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::BMS3;
			else if( FalconType->SelectedIndex == 3 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::BMS4;
			else if( FalconType->SelectedIndex == 4 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::OpenFalcon;
			else if( FalconType->SelectedIndex == 5 )
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::FreeFalcon5;
			else
				Saitek::MainThread->Config.FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
			
			try
			{
				FalconPath->Text = Saitek::MainThread->Config.FalconPaths[ Saitek::MainThread->Config.FalconType ];
			}
			catch( System::Collections::Generic::KeyNotFoundException^ )
			{
				FalconPath->Text = "";
			}
			
			try
			{
				FalconParameters->Text = Saitek::MainThread->Config.FalconParameters[ Saitek::MainThread->Config.FalconType ];
			}
			catch( System::Collections::Generic::KeyNotFoundException^ )
			{
				FalconParameters->Text = "";
			}
		}
private: System::Void SelectedConfig_SelectedIndexChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::InstancesLock->WaitOne();
			
			DeviceInstance *dev_inst = NULL;
			GUID guid;
			
			try
			{
				dev_inst = Saitek::Instances.at( InstanceListBox->SelectedIndex );
				guid = dev_inst->Guid;
			}
			catch( std::out_of_range e )
			{
			}
			
			if( dev_inst )
			{
				// Build a list of all applicable configs for this GUID.
				std::vector<DeviceConfig*> dev_confs;
				dev_confs.push_back( NULL );
				for( std::map<std::string, DeviceConfig*>::iterator conf_iter = Saitek::Configs.begin(); conf_iter != Saitek::Configs.end(); conf_iter ++ )
				{
					if( conf_iter->second->Guid == guid )
						dev_confs.push_back( conf_iter->second );
				}
				
				// Change the instance's config to the one we've selected.
				try
				{
					dev_inst->Config = dev_confs.at( SelectedConfig->SelectedIndex );
				}
				catch( std::out_of_range e )
				{
					dev_inst->Config = NULL;
				}
			}
			
			Saitek::InstancesLock->ReleaseMutex();
		}
private: System::Void FalconBrowseButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			// Keep track of the working directory.
			String ^working_dir = System::Environment::CurrentDirectory;
			
			OpenFileDialog ^falcon_exe_box = gcnew OpenFileDialog();
			falcon_exe_box->Filter = "Falcon 4 Executable (*.exe)|*.exe|All Files (*.*)|*.*";
			falcon_exe_box->ShowDialog();
			
			if( falcon_exe_box->FileName->Length )
				FalconPath->Text = falcon_exe_box->FileName;
			
			delete falcon_exe_box;
			
			// Restore the working directory.
			System::Environment::CurrentDirectory = working_dir;
		}
private: System::Void AutoLaunch_CheckedChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::MainThread->Config.AutoLaunch = AutoLaunch->Checked;
			
			FalconPath->Enabled = AutoLaunch->Checked;
			FalconBrowseButton->Enabled = AutoLaunch->Checked;
			FalconParameters->Enabled = AutoLaunch->Checked;
			FalconParametersLabel->Enabled = FalconParameters->Enabled;
		}
	private: System::Void ConfigListBox_SelectedIndexChanged( System::Object ^sender, System::EventArgs ^e )
		{
			DeviceConfig *dev_conf = NULL;
			
			int num = 0;
			for( std::map<std::string,DeviceConfig*>::iterator conf_iter = Saitek::Configs.begin(); conf_iter != Saitek::Configs.end(); conf_iter ++ )
			{
				if( num == ConfigListBox->SelectedIndex )
				{
					dev_conf = conf_iter->second;
					break;
				}
				num ++;
			}
			
			if( dev_conf )
			{
				ConfigName->Text = gcnew System::String(dev_conf->Name.c_str());
				
				if( dev_conf->Guid == DeviceType_X52Pro )
				{
					ConfigType->Text = "for X52 Pro";
					ConfigImage->ImageLocation = "Images/icon_x52pro.png";
				}
				else if( dev_conf->Guid == DeviceType_Fip )
				{
					ConfigType->Text = "for FIP";
					ConfigImage->ImageLocation = "Images/icon_fip.png";
				}
				else
				{
					ConfigType->Text = "for unknown device";
					ConfigImage->ImageLocation = "Images/icon_unknown.png";
				}
				
				EditConfigButton->Enabled = true;
				DeleteConfigButton->Enabled = ! Saitek::MainThread->Running;
			}
			else
			{
				ConfigName->Text = "(no configuration selected)";
				ConfigType->Text = "";
				ConfigImage->ImageLocation = "Images/icon_unknown.png";
				
				EditConfigButton->Enabled = false;
				DeleteConfigButton->Enabled = false;
			}
		}
private: System::Void FalconPath_TextChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::MainThread->Config.FalconPaths[ Saitek::MainThread->Config.FalconType ] = FalconPath->Text;
		}
private: System::Void FalconParameters_TextChanged( System::Object ^sender, System::EventArgs ^e )
		{
			Saitek::MainThread->Config.FalconParameters[ Saitek::MainThread->Config.FalconType ] = FalconParameters->Text;
		}
private: System::Void MainForm_FormClosing( System::Object ^sender, System::Windows::Forms::FormClosingEventArgs ^e )
		{
			Saitek::SaveConfigs();
		}
private: System::Void NewConfigButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			Raptor007sFalcon4toSaitekUtility::NewConfigForm ^new_window = gcnew Raptor007sFalcon4toSaitekUtility::NewConfigForm();
			new_window->Show();
		}
private: System::Void DeleteConfigButton_Click( System::Object ^sender, System::EventArgs ^e )
		{
			std::string cfg_name;
			
			int index = 0;
			for( std::map<std::string, DeviceConfig*>::iterator cfg_iter = Saitek::Configs.begin(); cfg_iter != Saitek::Configs.end(); cfg_iter ++ )
			{
				if( index == ConfigListBox->SelectedIndex )
					cfg_name = cfg_iter->second->Name;
				index ++;
			}
			
			if( cfg_name.size() )
			{
				System::String ^cfg_name_str = gcnew System::String(cfg_name.c_str());
				System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show( "Are you sure you want to delete " + cfg_name_str + ".cfg?", "Really Delete " + cfg_name_str + ".cfg?", System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Exclamation );
				if( result == System::Windows::Forms::DialogResult::Yes )
				{
					std::map< std::string, DeviceConfig* >::iterator cfg_iter = Saitek::Configs.find(cfg_name);
					if( cfg_iter != Saitek::Configs.end() )
					{
						// Lock threads while we muck about.
						Saitek::InstancesLock->WaitOne();
						
						// Unassign the config from any instances using it.
						for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
						{
							if( (*inst_iter)->Config == cfg_iter->second )
								(*inst_iter)->Config = NULL;
						}
						
						// Release thread lock.
						Saitek::InstancesLock->ReleaseMutex();
						
						delete cfg_iter->second;
						cfg_iter->second = NULL;
						Saitek::Configs.erase( cfg_iter );
					}
					
					Saitek::ConfigsChanged = true;
					
					try
					{
						ConfigListBox->SelectedIndex = -1;
					}
					catch( ... ){}
					
					ConfigListBox_Update( sender, e );
					
					std::string cmd = std::string("move \"Configs\\") + cfg_name + std::string(".cfg\" \"Configs\\") + cfg_name + std::string(".bak\"");
					system( cmd.c_str() );
				}
				delete cfg_name_str;
			}
		}
private: System::Void EmailLink_LinkClicked( System::Object ^sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^e )
		{
			System::Diagnostics::Process::Start( "mailto://blair@datapro.net" );
		}
};
}
