#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Raptor007sFalcon4toSaitekUtility {

	/// <summary>
	/// Summary for X52ProConfigForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class X52ProConfigForm : public System::Windows::Forms::Form
	{
	public:
		X52ProConfigForm(void)
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
		~X52ProConfigForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(X52ProConfigForm::typeid));
			this->SuspendLayout();
			// 
			// X52ProConfigForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"X52ProConfigForm";
			this->Text = L"X52 Pro";
			this->Load += gcnew System::EventHandler(this, &X52ProConfigForm::X52ProConfigForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void X52ProConfigForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
		}
	};
}
