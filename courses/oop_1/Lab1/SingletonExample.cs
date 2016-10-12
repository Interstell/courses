using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class SingletonExample{ 
        private static SingletonExample instance;

        static public SingletonExample Instance{
            get{
                if (instance == null)
                    instance = new SingletonExample();
                return instance;
            }
        }
        private SingletonExample(){}
        public void ShowInfo(){
            Console.WriteLine("Hello world!");
        }
    }
}
