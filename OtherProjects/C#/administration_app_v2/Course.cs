using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace administration_app
{
    class Course
    {
        private const int maxMembers = 3;
        private ProjectGroup projectGroup;
        private string groupName;
        private List<ProjectGroup> groups = new List<ProjectGroup>();
        private List<Student> enrolledStudents = new List<Student>();

        public string Name
        {
            get;
            set;
        }

        public Student[] Students
        {
            get  => enrolledStudents.ToArray();
        }

        public ProjectGroup[] Groups 
        {
            get => groups.ToArray();
        }

        public int StudentsCount
        {
            get => enrolledStudents.Count();
        }

        public int GroupsCount 
        {
            get => groups.Count();
        }

        public Course(string name) 
        {
            Name = name;
            this.groupName = $"PG1_{Name}";
            this.projectGroup = new ProjectGroup(groupName);
            this.groups.Add(projectGroup);
        }

        /// <summary>
        /// Add student method.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="stuId"></param>
        /// <returns>true or false statement.</returns>
        public bool AddStudent(string name, int stuId)
        {
            if (SearchByStudentNumber(stuId) != null)
            {
                return false;
            }
            else
            {
                if ((projectGroup.MembersCount != 0) && (projectGroup.MembersCount % maxMembers == 0))
                {
                    this.groupName = $"PG{GroupsCount + 1}_{Name}";
                    this.projectGroup = new ProjectGroup(groupName);
                    groups.Add(projectGroup);
                }

                Student newStudent = new Student(name, this.groupName, stuId);

                if (projectGroup.AddMember(newStudent))
                {
                    enrolledStudents.Add(newStudent);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        /// <summary>
        /// A method to search the students by their ID.
        /// </summary>
        /// <param name="query"></param>
        /// <returns>Student name.</returns>
        public Student SearchByStudentNumber(int query) 
        {
            foreach (Student eachStudent in enrolledStudents) 
            {
                if (eachStudent.StudentNumber == query) 
                {
                    return eachStudent;
                }
            }
            return null;
        }

        /// <summary>
        /// A method to search the student names by group.
        /// </summary>
        /// <param name="query"></param>
        /// <returns>Student names that are in the group.</returns>
        public Student[] SearchByGroup(string query) 
        {
            List<Student> newGroup = new List<Student>();
            int groupIndex = -1;
            bool found = false;
            int currentMaxGroupsCount = groups.Count();

            while (groupIndex < currentMaxGroupsCount && found == false)
            {
                groupIndex++;
                foreach (ProjectGroup group in groups)
                {
                    if (group.GroupName == query)
                    {
                        for (int i = 0; i < group.MembersCount; i++)
                        {
                            newGroup.Add(group.Members[i]);
                        }
                        found = true;
                    }
                }
            }

            return newGroup.ToArray();
        }
    }
}