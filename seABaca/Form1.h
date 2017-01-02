#pragma once


namespace seABaca {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Form1
	///
	/// ADVERTENCIA: si cambia el nombre de esta clase, deberá cambiar la
	///          propiedad 'Nombre de archivos de recursos' de la herramienta de compilación de recursos administrados
	///          asociada con todos los archivos .resx de los que depende esta clase. De lo contrario,
	///          los diseñadores no podrán interactuar correctamente con los
	///          recursos adaptados asociados con este formulario.
	/// </summary>
	AB nuevo;
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void) : arbolB(nuevo)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  tValor;



	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		AB &arbolB;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  button5;

	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tDelay;
	private: System::Windows::Forms::Button^  button9;





			 System::ComponentModel::Container ^components;
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->tValor = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tDelay = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::DarkSeaGreen;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(996, 506);
			this->panel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(6, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(155, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Visualizar recorrido inOrden";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(9, 39);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(117, 34);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Insertar en binario";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// tValor
			// 
			this->tValor->Location = System::Drawing::Point(52, 16);
			this->tValor->Name = L"tValor";
			this->tValor->Size = System::Drawing::Size(63, 20);
			this->tValor->TabIndex = 3;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(6, 51);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(155, 31);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Visualizar recorrido preOrden";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(6, 88);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(155, 31);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Visualizar recorrido postOrden";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(853, 528);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(853, 542);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(853, 556);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"label3";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(9, 79);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(117, 34);
			this->button5->TabIndex = 11;
			this->button5->Text = L"Borrar Ordenado";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click_1);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(906, 585);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(102, 32);
			this->button6->TabIndex = 13;
			this->button6->Text = L"Salir";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click_1);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(167, 19);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(103, 63);
			this->button7->TabIndex = 14;
			this->button7->Text = L"Chequear nodos Desbalanceados";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(149, 39);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(153, 74);
			this->button8->TabIndex = 15;
			this->button8->Text = L"Aplicar Rotación Simple (lado es calculado automáticamente)";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 23);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(40, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Valor : ";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button9);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->button8);
			this->groupBox1->Controls->Add(this->tValor);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Location = System::Drawing::Point(12, 525);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(495, 126);
			this->groupBox1->TabIndex = 17;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Operaciones de modificación";
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(324, 39);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(153, 74);
			this->button9->TabIndex = 17;
			this->button9->Text = L"Aplicar Rotación Doble (lado es calculado automáticamente)";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Location = System::Drawing::Point(513, 525);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(278, 127);
			this->groupBox2->TabIndex = 18;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Operaciones de Consulta";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(797, 638);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(146, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Delay animaciones en mSegs";
			// 
			// tDelay
			// 
			this->tDelay->Location = System::Drawing::Point(949, 635);
			this->tDelay->Name = L"tDelay";
			this->tDelay->Size = System::Drawing::Size(65, 20);
			this->tDelay->TabIndex = 10;
			this->tDelay->Text = L"1000";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1020, 663);
			this->ControlBox = false;
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->tDelay);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"Form1";
			this->Text = L"SeABaca - (Simulador Experto de Arboles Binarios a cabalidad) - Por Randall Varga" 
				L"s Li - Universidad Latina de Costa Rica";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				
				//arbolB.insertar(1, panel1);
				//arbolB.insertar(7, panel1);
				//arbolB.insertar(14, panel1);
				//arbolB.insertar(3, panel1);
				//arbolB.insertar(5, panel1);
				//arbolB.insertar(53, panel1);
				

				 arbolB.RecorreInOrden(panel1, Convert::ToInt32(tDelay->Text::get()));
				MessageBox::Show("Animación completada!");
				
				
				
				/*arbolB.insertar(12);
				arbolB.insertar(18);
				arbolB.insertar(11);
				arbolB.insertar(6);
				arbolB.insertar(3);
				arbolB.insertar(22);
				arbolB.insertar(57);
				arbolB.insertar(19);
				arbolB.insertar(8);
				arbolB.insertar(4);
				
				arbolB.insertar(15);
				arbolB.insertar(16);
				arbolB.insertar(7);
				*/
				//arbolB.insertar(21);
				//arbolB.insertar(28);

				
					


				//util util;
				//Pen^ pcolor = gcnew Pen(System::Drawing::Color::Black);
				
				//util.mueveNodo(7, 11, 321, 135, 230, panel1);
				 


			 }

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {


				 int val;

				 try{
					 val = Convert::ToInt32(tValor->Text::get());
				 }
				 catch(Exception^ e){
					 MessageBox::Show("Debe de digitar solo números enteros. Error : " + e->Message);
					 return;
				 }

				 arbolB.insertar(val, panel1);


				 //calcula altura
				 util util;
				 
				 label1->Text::set("Altura del árbol : " + util.CalculAlturArbol(arbolB, panel1).ToString());
				 label2->Text::set("Total nodos : " + util.infoNodo(arbolB, "nodos").ToString());
				 label3->Text::set("Hojas del árbol : " + util.infoNodo(arbolB, "hojas").ToString());


				 
				 
			 
			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {


				arbolB.RecorrePreOrden(panel1, Convert::ToInt32(tDelay->Text::get()));
				MessageBox::Show("Animación completada!");
				

		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {


				arbolB.RecorrePostOrden(panel1, Convert::ToInt32(tDelay->Text::get()));
				MessageBox::Show("Animación completada!");
				

		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {


			 


		 }
private: System::Void button5_Click_1(System::Object^  sender, System::EventArgs^  e) {



			 int val;

			 try{
				 val = Convert::ToInt32(tValor->Text::get());
			 }
			 catch(Exception^ e){
				 MessageBox::Show("Debe de digitar solo números enteros. Error : " + e->Message);
				 return;
			 }

			 arbolB.borraOrdenado(val, panel1);

			 //calcula altura
			 util util;
				 
			 label1->Text::set("Altura del árbol : " + util.CalculAlturArbol(arbolB, panel1).ToString());
			 label2->Text::set("Total nodos : " + util.infoNodo(arbolB, "nodos").ToString());
			 label3->Text::set("Hojas del árbol : " + util.infoNodo(arbolB, "hojas").ToString());


		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {





		 }
private: System::Void button6_Click_1(System::Object^  sender, System::EventArgs^  e) {


			/* arbolB.insertar(55, panel1);
			 arbolB.insertar(65, panel1);
	         arbolB.insertar(75, panel1);
			 arbolB.insertar(78, panel1);
			 arbolB.insertar(73, panel1);
	         arbolB.insertar(71, panel1);
	         arbolB.insertar(76, panel1);
			 arbolB.insertar(80, panel1);
			 arbolB.insertar(77, panel1);
*/

			 //arbolB.insertar(25,panel1);
			 //arbolB.insertar(15,panel1);
			 //arbolB.insertar(12,panel1);
			 //arbolB.insertar(35,panel1);
			 //arbolB.insertar(45,panel1);
			 //arbolB.insertar(24,panel1);
			 //arbolB.insertar(22,panel1);
			 //arbolB.insertar(7,panel1);
			 //arbolB.insertar(3,panel1);
			 //arbolB.insertar(8,panel1);

			 //arbolB.insertar(23,panel1);
			 //arbolB.insertar(29,panel1);
			 //arbolB.insertar(25,panel1);
			 //arbolB.insertar(27,panel1);
			 //arbolB.insertar(26,panel1);
			 //arbolB.insertar(24,panel1);
			 //arbolB.insertar(11,panel1);

		

			 	////calcula altura
				 //util util;
				 //
				 //label1->Text::set("Altura del árbol : " + util.CalculAlturArbol(arbolB, panel1).ToString());
				 //label2->Text::set("Total nodos : " + util.infoNodo(arbolB, "nodos").ToString());
				 //label3->Text::set("Hojas del árbol : " + util.infoNodo(arbolB, "hojas").ToString());


			 MessageBox::Show("Creado por Ing. Randall Vargas Li - Universidad Latina de Costa Rica - Email: ranvlicr@gmail.com / mobile: 8847-3530");


			 exit(0);

			 


		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {


			 arbolB.checkAVL(arbolB.raiz);



		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {




			 int val;

			 try{
				 val = Convert::ToInt32(tValor->Text::get());
			 }
			 catch(Exception^ e){
				 MessageBox::Show("Debe de digitar solo números enteros. Error : " + e->Message);
				 return;
			 }


			 
			 arbolB.aplicaRotacionSimple(val, panel1, Convert::ToInt32(tDelay->Text::get()));

			 	
			 //calcula altura y fbs
				 util util;
				 
				 label1->Text::set("Altura del árbol : " + util.CalculAlturArbol(arbolB, panel1).ToString());
				 label2->Text::set("Total nodos : " + util.infoNodo(arbolB, "nodos").ToString());
				 label3->Text::set("Hojas del árbol : " + util.infoNodo(arbolB, "hojas").ToString());

		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {



			 
			 int val;

			 try{
				 val = Convert::ToInt32(tValor->Text::get());
			 }
			 catch(Exception^ e){
				 MessageBox::Show("Debe de digitar solo números enteros. Error : " + e->Message);
				 return;
			 }


			 
			 arbolB.aplicaRotacionDoble(val, panel1, Convert::ToInt32(tDelay->Text::get()));

			 	
			 //calcula altura y fbs
				 util util;
				 
				 label1->Text::set("Altura del árbol : " + util.CalculAlturArbol(arbolB, panel1).ToString());
				 label2->Text::set("Total nodos : " + util.infoNodo(arbolB, "nodos").ToString());
				 label3->Text::set("Hojas del árbol : " + util.infoNodo(arbolB, "hojas").ToString());



		 }
};
}

