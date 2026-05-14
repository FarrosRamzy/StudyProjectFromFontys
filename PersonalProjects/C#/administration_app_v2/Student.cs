using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace administration_app
{
    class Student
    {
        private string name;
        private int idNumber;
        private string groupName;

        public string Name 
        {
            get => name;
        }

        public int StudentNumber 
        {
            get => idNumber;
        }

        /// <summary>
        /// Add a student from course in students.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="groupName"></param>
        /// <param name="studentId"></param>
        public Student(string name, string groupName, int studentId) 
        {
            this.name = name;
            this.groupName = groupName;
            this.idNumber = studentId;
        }

        /// <summary>
        /// Give the class info to the form.
        /// </summary>
        /// <returns>Students basic data information as a string.</returns>
        public string GetInfo() 
        {
            return $"{name}  ({idNumber}) - {groupName}";
        }
    }
}