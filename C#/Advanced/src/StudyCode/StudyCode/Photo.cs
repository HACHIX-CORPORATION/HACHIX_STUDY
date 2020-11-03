using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudyCode
{
    public class Photo
    {
        public static Photo Load(string path)
        {
            Console.WriteLine("load");
            return new Photo();
        }

        public void Save()
        {
            Console.WriteLine("save");
        }
    }
}
