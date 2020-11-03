using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudyCode
{
    public class PhotoProcessor
    {
        public delegate void PhotoFilterHandler(Photo photo);

        // Solution without delegate
        // Process bị cố định bởi những process nên solution này không flexible
        public void Process(string path)
        {
            var photo = Photo.Load(path);

            var filter = new PhotoFilter();
            filter.AppplyBrightness(photo);
            filter.AppplyConstrast(photo);
            filter.AppplyResize(photo);

            photo.Save();
        }

        // Delegateには一つの関数ではなく、関数のGroupを登録することができる。
        public void Process2(string path, PhotoFilterHandler filterHandler)
        {
            var photo = Photo.Load(path);

            filterHandler(photo);

            photo.Save();
        }
    }
}
