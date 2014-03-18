using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK.Graphics.OpenGL;

namespace Lab1CC
{
    public partial class Form1 : Form
    {
        int i = 0, x1 = 0, y1 = 0, x0 = 0, y0 = 0, sx = 0, sy = 0;
        float x = 0, y = 0, dx = 0, dy = 0, l = 0;
        bool loaded = false;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            loaded = true; GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);
            GL.ClearColor(Color.Black);
            SetupViewport();
        }

        private void SetupViewport()
        {
            int w = glControl.Width;
            int h = glControl.Height;
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();
            GL.Ortho(0, w, 0, h, -1, 1); // Верхний левый угол имеет кооординаты(0, 0)
            GL.Viewport(0, 0, w, h); // Использовать всю поверхность GLControl под рисование
        }


        private void glControl1_Resize(object sender, EventArgs e)
        {
            if (!loaded)
                return;
        }

        private void paint(object sender, PaintEventArgs e)
        {
            if (!loaded) //Пока контекст не создан
                return;
        }

        private void btn_grid_Click(object sender, EventArgs e)
        {
            DrawGrid();
        }

        private void DrawGrid()
        {
            x0 = 0;
            y0 = 0;
            x = 800;
            y = 600;

            GL.LineWidth(3f);
            GL.Color3(Color.White);
            GL.Begin(BeginMode.Lines);

            GL.Vertex2(405f, 0);
            GL.Vertex2(405f, 800f);
            GL.Vertex2(0, 300f);
            GL.Vertex2(800f, 300f);
            GL.End();
            while (x0 <= x)
            {
                GL.LineWidth(1f);
                GL.Begin(BeginMode.Lines);

                GL.Color3(Color.White);
                GL.Vertex2(x0, 0);
                GL.Vertex2(x0, 600f);
                x0 += 15;
                GL.End();
            }
            while (y0 <= y)
            {
               
                GL.Begin(BeginMode.Lines);
                GL.LineWidth(1f);
                GL.Color3(Color.White);
                GL.Vertex2(0, y0);
                GL.Vertex2(800, y0);
                GL.End();
                y0 += 15;
            }
            // glControl.SwapBuffers();
        }

        private void DrawVector()
        {
            try
            {
                x0 = Convert.ToInt32(textBox1.Text);
                y0 = Convert.ToInt32(textBox2.Text);
                x1 = Convert.ToInt32(textBox3.Text);
                y1 = Convert.ToInt32(textBox4.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Проверьте заполнение полей для ввода");
            }
            GL.LineWidth(2f);
            GL.Begin(BeginMode.Lines);
            GL.Color3(Color.Red);
            GL.Vertex2(x0 * 15 + 405, y0 * 15 + 300);
            GL.Vertex2(x1 * 15 + 405, y1 * 15 + 300);
            GL.End();

        }

        private void button4_Click(object sender, EventArgs e)
        {
            glControl.SwapBuffers();
        }

        private void DrawCDA()
        {
            try
            {
                x0 = Convert.ToInt32(textBox1.Text);
                y0 = Convert.ToInt32(textBox2.Text);
                x1 = Convert.ToInt32(textBox3.Text);
                y1 = Convert.ToInt32(textBox4.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Проверьте заполнение полей для ввода");
            }
            x = Math.Abs(x1 - x0); y = Math.Abs(y1 - y0);     //начальные координаты
            if (x >= y) l = x; else l = y;     //определение l


            try
            {
                dx = (x1 - x0) / l;
                dy = (y1 - y0) / l; //приращения
            }
            catch (Exception ex)
            {
                MessageBox.Show("Длина не может быть равно 0");//ошибка при вводе в edit не числа
                return;
            }
            if (dx > 0) sx = 1; else sx = -1;  //знаки приращений
            if (dy > 0) sy = 1; else sy = -1;
            x = Convert.ToSingle(x0 + 0.5 * sx); y = Convert.ToSingle(y0 + 0.5 * sy);
            for (i = 0; i != l; i++)
            { //рисуем пикселы

                GL.Color3(Color.Blue);
                GL.Rects((short)(Math.Floor(x) * 15 + 404), (short)(Math.Floor(y) * 15 + 300), 
                    (short)(Math.Floor(x) * 15 + 420), (short)(Math.Floor(y) * 15 + 316));

                x = x + dx; y = y + dy;
            }
        }

        private void DrawBrezenhem()
        {
            
            try
            {
                x0 = Convert.ToInt32(textBox1.Text);
                y0 = Convert.ToInt32(textBox2.Text);
                x1 = Convert.ToInt32(textBox3.Text);
                y1 = Convert.ToInt32(textBox4.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Проверьте заполнение полей для ввода");
            }
            int a = 0, b = 0, e = 0;

            x = x0; y = y0;
            dx = Math.Abs(x1 - x0); dy = Math.Abs(y1 - y0);
            if ((x1 - x0) >= 0) sx = 1; else sx = -1;
            if ((y1 - y0) >= 0) sy = 1; else sy = -1;
            if (dy > dx)
            {
                a = Convert.ToInt32(dx); dx = dy; dy = a; b = 1;
            }
            else b = 0;
            e = Convert.ToInt32(2 * dy - dx);
            for (i = 0; i != dx; i++)
            {
                GL.Color3(Color.Yellow);
                GL.Rects((short)(x * 15 + 405), (short)(y * 15 + 301), (short)(x * 15 + 421), (short)(y * 15 + 316));
                while (e >= 0)
                {
                    if (b == 1) x = x + sx; else y = y + sy;
                    e = e - Convert.ToInt32(2 * dx);
                }
                if (b == 1) y = y + sy; else x = x + sx;
                e = e + Convert.ToInt32(2 * dy);
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            GL.Clear(ClearBufferMask.DepthBufferBit|ClearBufferMask.ColorBufferBit);
            GL.ClearColor(Color.Black);
            if (checkBox1.Checked)
                DrawGrid();
            if (checkBox3.Checked)
                DrawCDA();
            if (checkBox4.Checked)
                DrawBrezenhem();
            if (checkBox2.Checked)
                DrawVector();

            glControl.SwapBuffers();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            GL.Clear(ClearBufferMask.DepthBufferBit | ClearBufferMask.ColorBufferBit);
            GL.ClearColor(Color.Black);
            glControl.SwapBuffers();
        }
    }
}
