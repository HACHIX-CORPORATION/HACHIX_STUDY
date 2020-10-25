using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Excersise
{
    class Program
    {
        static void Main(string[] args)
        {
            // theo như trang HowKteam em học thì người ta viest Region ở vị trí này

            //Đề bài: Nhập vào 2 giá trị rồi xuất ra các biểu thức toán học với 2 giá trị đó
            #region Bai tap 
            int x = 0;
            while(x <3)
            {
                int firstNumber;
                int secondNumber;

                Console.Write("firstnumber =  ");
                firstNumber = Int32.Parse(Console.ReadLine());

                Console.Write("secondnumber = ");
                secondNumber = Int32.Parse(Console.ReadLine());

                PrintSumoftwonumbers(firstNumber, secondNumber);
                Console.ReadLine();

                x++;
            }
          //x++; Trả lời cho câu hỏi số 7 (Vì sao lặp hơn 4 lần)
        }
        
        static void PrintSumoftwonumbers(int firstNumber, int secondNumber)
        {
            if (firstNumber < 10)
            {
                for (int count = 0 ; count < 10 ; count++)
                {
                    firstNumber += count;
                    secondNumber = secondNumber + count* 2 % 5;
                    Console.WriteLine("{0} + {1} = {2}", firstNumber, secondNumber, Sumoftwonumbers(firstNumber, secondNumber));
                }
            }

            else
            {
                for (int count =0 ; count < 10; count++)
                {
                    firstNumber += count;
                    secondNumber = secondNumber+2*count;
                    Console.WriteLine("{0} + {1} = {2}", firstNumber, secondNumber, Sumoftwonumbers(firstNumber, secondNumber));
                }
            }
            
        }

        static int Sumoftwonumbers(int firstNumber, int secondNumber)
        {
            return firstNumber + secondNumber;
        }
        #endregion

    }
}
