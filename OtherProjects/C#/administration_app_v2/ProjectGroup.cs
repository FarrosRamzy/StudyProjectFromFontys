using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace administration_app
{
    class ProjectGroup
    {
        private string groupName;
        private List<Student> members = new List<Student>();

        public int MembersCount
        {
            get => members.Count();
        }

        public string GroupName
        {
            get => groupName;
        }

        public Student[] Members 
        {
            get => members.ToArray(); 
        }

        /// <summary>
        /// Construct the new project group class.
        /// </summary>
        /// <param name="groupName"></param>
        public ProjectGroup(string groupName)
        {
            this.groupName = groupName;
        }

        /// <summary>
        /// Add a student as a member if they are not added yet and the group still have at least one space.
        /// </summary>
        /// <param name="student"></param>
        /// <returns>true or false.</returns>
        public bool AddMember(Student student)
        {
            bool newMemberAdded = false;
            if (members.Count != 0)
            {
                if (members.Contains(student))
                {
                    newMemberAdded = false;
                }
                else
                {
                    members.Add(student);
                    newMemberAdded = true;
                }
            }
            else
            {
                members.Add(student);
                newMemberAdded = true;
            }
            return newMemberAdded;
        }
    }
}