using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Data.OleDb;
using System.Diagnostics;
using System.Security.Cryptography;
using Rijndael256;
using Rijndael = Rijndael256.Rijndael;

namespace AES_DES
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        // DES
        public string[] stringArr_NhiPhan(string key)
        {

            string[] keyBinaryArray = DES.HexToBin4bit(key);
            return keyBinaryArray;
        }

        public void Key_Binary()
        {
            string temp = "";
            foreach (var item in stringArr_NhiPhan(txtKhoaK.Text))
            {
                temp += (item + " ");
            }
            txtKetQua.AppendText("  K nhị phân: " + temp + Environment.NewLine);
        }

        public void tim_K_table(string[] matranPC02_Array)
        {
            for (int i = 0; i < 16; i++)
            {
                string[] key_Array = new string[56];
                key_Array = DES.hoanVi(matranPC02_Array, DES.listCnDn[i], 48);
                DES.key_List.Add(key_Array);
            }

            for (int k = 0; k < 16; k++)
            {
                txtKetQua.AppendText("  K" + (k + 1) + " :");
                if (k < 9) txtKetQua.AppendText("  ");
                for (int j = 0; j < 48; j++)
                {
                    txtKetQua.AppendText(DES.key_List[k][j].ToString() + " ");

                }
                txtKetQua.AppendText(Environment.NewLine);
            }
        }

        public void HoanViKey()
        {
            string[] binaryStr64 = DES.Convert_16unit4bit_To_64unit1bit(stringArr_NhiPhan(txtKhoaK.Text));
            string[] strArray = DES.hoanVi(DES.MT_PC1, binaryStr64, 56);
            string temp = "";

            for (int i = 0; i < strArray.Length; i++)
            {
                temp += strArray[i];
                if ((i + 1) % 4 == 0) temp += " ";
            }

            txtKetQua.AppendText("  K hoán vị  : " + temp + Environment.NewLine);
        }

        public void CnDnTable()
        {
            string[] binaryStr64 = DES.Convert_16unit4bit_To_64unit1bit(stringArr_NhiPhan(txtKhoaK.Text));
            string[] keyHoanVi = DES.hoanVi(DES.MT_PC1, binaryStr64, 56);
            DES.CnDnTable(DES.Dich_CnDn, keyHoanVi);

            txtKetQua.AppendText(Environment.NewLine);
            for (int i = 0; i <= 16; i++)
            {

                txtKetQua.AppendText("  C" + i + ": ");
                if (i <= 9) txtKetQua.AppendText("  ");
                for (int j = 0; j < 28; j++)
                {

                    txtKetQua.AppendText((DES.listCn[i][j] + " "));
                }
                txtKetQua.AppendText("|D" + i + ": ");
                if (i <= 9) txtKetQua.AppendText("  ");
                for (int j = 0; j < 28; j++)
                {

                    txtKetQua.AppendText((DES.listDn[i][j] + " "));

                }
                txtKetQua.AppendText(Environment.NewLine);
            }
        }
        public void TimLnRn_MaHoa(string plainText)
        {
            tim_K_table(DES.MT_PC2);
            for (int i = 0; i < 16; i++)
            {

                DES.L0R0(stringArr_NhiPhan(plainText));
                string[] f = DES.KeyXorER(DES.key_List[i], DES.listRn[i]);//xong b1;

                string[] Bn_array = DES.Bn(f);//xong b2;
                DES.listSboxOut.Add(Bn_array);
                //thuc hien buoc 3;
                //ket qua ra S1(B1) -> S8(B8)
                DES.timXY(Bn_array);
                DES.hoanViFquaSBox(Bn_array);
                string[] tempSnBn = DES.DecimalToBin4bit(DES.SnBnArray);
                DES.listSnBnArray.Add(tempSnBn);
                //hoan vi cua f(R0,K1) ;
                string[] binaryStr = DES.Convert_8unit4bit_To_32unit1bit(tempSnBn);
                string[] F_RK = DES.hoanVi(DES.MT_P, binaryStr, 32);
                DES.listFRK.Add(F_RK);
                string[] temp = DES.listRn[i];
                DES.listLn.Insert(i + 1, temp);

                string[] temp2 = DES.L_Xor_F_RK(DES.listLn[i], F_RK);
                DES.listRn.Insert(i + 1, temp2);

            }

        }

        public void TimLR_GiaiMa(string cypher)
        {

            Key_Binary();

            //hoan vi khoa 56 bit
            HoanViKey();

            //bang dich theo key theo bang CnDn
            CnDnTable();
            tim_K_table(DES.MT_PC2);
            string cypherText = cypher;
            string[] ipNegative1 = DES.HexToBin4bit(cypherText);
            ipNegative1 = DES.Convert_16unit4bit_To_64unit1bit(ipNegative1);
            string[] L16R16 = DES.hoanViNguoc(DES.MT_IP_negative1, ipNegative1);
            //txtKetQua.AppendText(string.Join("", ipNegative1));
            // txtKetQua.AppendText("\r\nL16R16: "+string.Join("",L16R16));
            string[] temp = new string[32];

            for (int j = 0; j < 32; j++)
            {
                temp[j] = L16R16[j];
            }
            DES.listLn.Add(temp);
            temp = new string[32];
            int index = 0;
            for (int j = 32; j < 64; j++)
            {
                temp[index] = L16R16[j];
                index++;
            }
            DES.listRn.Add(temp);
            int ind = 0;
            for (int i = 15; i >= 0; i--)
            {


                string[] f = DES.KeyXorER(DES.key_List[i], DES.listRn[ind]);//xong b1;

                string[] Bn_array = DES.Bn(f);//xong b2;
                DES.listSboxOut.Add(Bn_array);
                //thuc hien buoc 3;
                //ket qua ra S1(B1) -> S8(B8)
                DES.timXY(Bn_array);
                DES.hoanViFquaSBox(Bn_array);
                string[] tempSnBn = DES.DecimalToBin4bit(DES.SnBnArray);
                DES.listSnBnArray.Add(tempSnBn);
                //hoan vi cua f(R0,K1) ;
                string[] binaryStr = DES.Convert_8unit4bit_To_32unit1bit(tempSnBn);
                string[] F_RK = DES.hoanVi(DES.MT_P, binaryStr, 32);
                DES.listFRK.Add(F_RK);
                string[] temp1 = DES.listRn[ind];

                DES.listLn.Insert(ind + 1, temp1);

                string[] temp2 = DES.L_Xor_F_RK(DES.listLn[ind], F_RK);
                DES.listRn.Insert(ind + 1, temp2);
                ind++;
            }
        }
        
        private bool isComparisonVisible = false;
        private void btnSoSanh_Click(object sender, EventArgs e)
        {
            isComparisonVisible = !isComparisonVisible;
            txtKetQua.Visible = isComparisonVisible;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btnMaHoa_Click(object sender, EventArgs e)
        {
            

            if (rdDES.Checked)
            {
                Stopwatch st = new Stopwatch();
                st.Start();
                txtKetQua.Clear();
                if (txtKhoaK.Text.Length != 16)
                {
                    MessageBox.Show("  Độ dài K phải = 16!", "Thông báo");
                    return;
                }
                if (txtBanRo.Text == "")
                {
                    MessageBox.Show("Mời bạn nhập dữ liệu cần mã hóa!", "Thông báo",MessageBoxButtons.OK);
                    return;
                }
                string cypherText = "";
                string plainText = txtBanRo.Text;
                txtDESbanro.Text = plainText;
                if (plainText.Length % 16 != 0)
                {
                    while (plainText.Length % 16 != 0)
                    {
                        plainText += "Z";
                    }
                }
               
                txtBanRo.Text = plainText;
                string[] plainTextArray = new string[plainText.Length / 16];
                int index = 0;
                for (int i = 0; i < plainTextArray.Length; i++)
                {
                    plainTextArray[i] = plainText.Substring(index, 16);
                    index += 16;
                }

                txtKetQua.AppendText("  Bản rõ chia thành các đoạn: ");
                txtKetQua.AppendText(Environment.NewLine);
                for (int i = 0; i < plainTextArray.Length; i++)
                {
                    txtKetQua.AppendText("  Đoạn " + (i + 1) + ": ");
                    txtKetQua.AppendText(plainTextArray[i]);
                    txtKetQua.AppendText(Environment.NewLine);
                }
                for (int k = 0; k < plainTextArray.Length; k++)
                {

                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  Đoạn rõ " + (k + 1) + ": " + plainTextArray[k]); txtKetQua.AppendText(Environment.NewLine);
                    plainText = plainTextArray[k];
                    //bien doi key - > nhi phan
                    Key_Binary();

                    //hoan vi khoa 56 bit
                    HoanViKey();

                    //bang dich theo key theo bang CnDn
                    CnDnTable();

                    //bang key tu 1->16

                    txtKetQua.AppendText(Environment.NewLine);
                    //DES.LnRn(stringArr_NhiPhan(txtBanRo.Text));

                    TimLnRn_MaHoa(plainText);
                    // 16 vong DES
                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  L0:" + string.Join("", DES.listLn[0]));
                    txtKetQua.AppendText("  R0:" + string.Join("", DES.listRn[0]));
                    for (int i = 1; i <= 16; i++)
                    {
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("----------------------------------------------------------------------Vòng " + i + "---------------------------------------------------------------");


                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  L" + i + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listLn[i].Length; j++)
                            txtKetQua.AppendText(DES.listLn[i][j]);

                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  E(R" + (i - 1) + ") :"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listE_R[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  K" + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.key_List[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  ER" + (i - 1) + " XOR K" + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listERXorK[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  SBox_Out " + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listSboxOut[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  S" + (i) + "  B" + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listSnBnArray[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  F(R" + (i - 1) + "K" + (i) + "):"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listFRK[i - 1]));

                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  L" + (i - 1) + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listLn[i].Length; j++)
                            txtKetQua.AppendText(DES.listLn[i - 1][j] + " ");
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  R" + i + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listRn[i].Length; j++)
                            txtKetQua.AppendText(DES.listRn[i][j] + " ");

                    }
                    string[] R16L16 = DES.listRn[16].Concat(DES.listLn[16]).ToArray();
                    string[] hoanviIpNegative1 = DES.hoanVi(DES.MT_IP_negative1, R16L16, 64);

                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText(Environment.NewLine);
                    string hoanviIpNegative1Str = string.Join("", hoanviIpNegative1);
                    txtKetQua.AppendText("  IP-1:" + hoanviIpNegative1Str);
                    cypherText += DES.binary4bitToHexDecimal(hoanviIpNegative1Str); txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  Bản mã của đoạn: " + DES.binary4bitToHexDecimal(hoanviIpNegative1Str)); txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("_____________________________________________________________________________________"); txtKetQua.AppendText(Environment.NewLine);
                    DES.DisposeAll();
                }
                txtMaHoa.Text = cypherText;
                txtDESbanma.Text = cypherText;
                st.Stop();
                txtDEStocdoMH.Text = st.ElapsedMilliseconds.ToString();
            }
            else if (rdAES.Checked)
            {
                Stopwatch st1 = new Stopwatch();
                st1.Start();
                txtKetQua.Text = "";
                var inputText = txtBanRo.Text;
                txtAESbanro.Text = inputText;
                var key = txtKhoaK.Text;
                string EncryptText = Rijndael.Encrypt(inputText, key, KeySize.Aes256);
                txtMaHoa.Text = EncryptText;
                txtAESbanma.Text = EncryptText;
                txtKetQua.AppendText("Bản mã là: " + EncryptText);
                st1.Stop();
                txtAEStocdoMH.Text = st1.ElapsedMilliseconds.ToString();
            }
            else
            {
                MessageBox.Show("Thông báo!", "Vui lòng chọn DES hoặc AES để tiếp tục !!!", MessageBoxButtons.OK);
            }
        }

        private void btnGiaiMa_Click(object sender, EventArgs e)
        {
            Stopwatch st3 = new Stopwatch();
            st3.Start();
            if (rdDES.Checked)
            {
                txtKetQua.Clear();
                if (txtKhoaK.Text.Length != 16)
                {
                    MessageBox.Show("  Độ dài K phải = 16!", "Thông báo");
                    return;
                }
                if (txtMaHoa.Text == "")
                {
                    MessageBox.Show("Mời bạn nhập dữ liệu cần giải mã!", "Thông báo");
                    return;
                }
                string cypher = "";
                string cypherText1 = txtMaHoa.Text;
                if(cypherText1.Length % 16 != 0)
                {
                    while (cypherText1.Length % 16 != 0)
                    {
                        cypherText1 += "F";
                    }
                }              
                txtMaHoa.Text = cypherText1;
                string[] cypherTextArray = new string[cypherText1.Length / 16];
                int index1 = 0;
                for (int i = 0; i < cypherTextArray.Length; i++)
                {
                    cypherTextArray[i] = cypherText1.Substring(index1, 16);
                    index1 += 16;
                }

                txtKetQua.AppendText("  Bản mã chia thành các đoạn: ");
                txtKetQua.AppendText(Environment.NewLine);
                for (int i = 0; i < cypherTextArray.Length; i++)
                {
                    txtKetQua.AppendText("  Đoạn " + (i + 1) + ": ");
                    txtKetQua.AppendText(cypherTextArray[i]);
                    txtKetQua.AppendText(Environment.NewLine);
                }
                for (int k = 0; k < cypherTextArray.Length; k++)
                {

                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  Đoạn rõ " + (k + 1) + ": " + cypherTextArray[k]); txtKetQua.AppendText(Environment.NewLine);
                    cypher = cypherTextArray[k];

                    TimLR_GiaiMa(cypher);
                    string[] R0L0 = DES.listRn[16].Concat(DES.listLn[16]).ToArray();
                    string[] cypherText = DES.hoanViNguoc(DES.MT_IP, R0L0);

                    string banRoCuaDoan = DES.binary4bitToHexDecimal(string.Join("", cypherText));
                    txtBanRo.Text += banRoCuaDoan;

                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  L0:" + string.Join("", DES.listLn[0]));
                    txtKetQua.AppendText("  R0:" + string.Join("", DES.listRn[0]));
                    int index = 16;
                    for (int i = 1; i <= 16; i++)
                    {
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("----------------------------------------------------------------------Vòng " + i + "---------------------------------------------------------------");


                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  L" + i + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listLn[i].Length; j++)
                            txtKetQua.AppendText(DES.listLn[i][j]);

                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  E(R" + (i - 1) + ") :"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listE_R[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  K" + (index) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.key_List[index - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  ER" + (i - 1) + " XOR K" + (index) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listERXorK[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  SBox_Out " + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listSboxOut[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  S" + (i) + "  B" + (i) + ":"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listSnBnArray[i - 1]));
                        txtKetQua.AppendText(Environment.NewLine);

                        txtKetQua.AppendText("  F(R" + (i - 1) + "K" + (index) + "):"); if (i <= 9) txtKetQua.AppendText("  ");
                        txtKetQua.AppendText(string.Join(" ", DES.listFRK[i - 1]));

                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  L" + (i - 1) + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listLn[i].Length; j++)
                            txtKetQua.AppendText(DES.listLn[i - 1][j] + " ");
                        txtKetQua.AppendText(Environment.NewLine);
                        txtKetQua.AppendText("  R" + i + " :"); if (i <= 9) txtKetQua.AppendText("  ");
                        for (int j = 0; j < DES.listRn[i].Length; j++)
                            txtKetQua.AppendText(DES.listRn[i][j] + " ");

                        index--;



                    }

                    txtKetQua.AppendText(Environment.NewLine);
                    txtKetQua.AppendText("  Bản rõ của đoạn: " + banRoCuaDoan);
                    txtKetQua.AppendText(Environment.NewLine);

                    DES.DisposeAll();
                }

                txtKetQua.AppendText("_____________________________________________________________________________________"); txtKetQua.AppendText(Environment.NewLine);
                st3.Stop();
                txtDEStocdoGM.Text = st3.ElapsedMilliseconds.ToString();
            }
            else if (rdAES.Checked)
            {
                Stopwatch st4 = new Stopwatch();
                st4.Start();
                txtKetQua.Text = "";
                var inputText = txtMaHoa.Text;
                string key = txtKhoaK.Text;
                string DecryptText = Rijndael.Decrypt(inputText, key, KeySize.Aes256);
                txtBanRo.Text = DecryptText;
                txtKetQua.AppendText("Bản rõ là: "+ DecryptText);
                st4.Stop();
                txtAEStocdoGM.Text = st4.ElapsedMilliseconds.ToString();
            }
            else
            {
                MessageBox.Show("Thông báo!", "Vui lòng chọn DES hoặc AES để tiếp tục !!!", MessageBoxButtons.OK);
            }
        }
    }
}
