using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectOrientedProgramming
{
    //class HachiX
    //{
    //    // khai báo các thuộc tính trong class
    //    public string Project;
    //    public string Language;

    //    //khai báo phương thức cho class

    //    public void Doing()
    //    {
    //        Console.WriteLine("Dang lam du an: " + Project + " bang: " + Language); 
    //    }

    //}

    class Project
    {
        // khai bao thuoc tinh
        public string ProjectName;
        public string ProjectLanguage;

        class Program
        {
            static void Main(string[] args)
            {
                Project Project1 = new Project("Yanmar", "Python");
                Project1.Doing();

                Project Project2 = new Project("FaceRecord", "JavaScrip");
                Project2.Doing();

                Console.Read();
            }
        }

        #region  Constractor without parameter 
        //khai bao constructor khong co tham so  
        //public Project()
        //{
        //    ProjectName = "Yanmar";
        //    ProjectLanguage = "Python";
        //}
        #endregion

        #region Constractor with parameter
        public Project(string projectname, string projectlanguage)
        {
            ProjectName = projectname;
            ProjectLanguage = projectlanguage;
        }
        
        public void Doing()
        {
            Console.WriteLine("Lam du an: " + ProjectName + " bang: " + ProjectLanguage);
        }
        #endregion

    }

    
}
