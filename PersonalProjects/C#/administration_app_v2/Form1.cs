using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace administration_app
{
    //////////////////////////////////////////////////////////////////////
    //administration_app
    //
    //Course	    : Programming in C# 2 (PCS2)
    //Assignment	: Small Assignment 1
    //Date		    : 25-02-2022
    //Student	    : Farros Ramzy (3767353)
    //Teacher       : Gastel, Franco F.J.P.M. van
    //
    //////////////////////////////////////////////////////////////////////

    /**
     * 
     * This is an app for the students administration.
     * 
     * FEATURES:
     * - Form1.cs
     * - Student.cs
     * - Courses.cs
     * - ProjectGroup.cs
     * 
     */
    public partial class Form1 : Form
    {

        private Course course;
        string name;
        int idNum;

        string courseName = "PCS2";

        bool couldAdd;                  //A boolean to determine if student can be added or not.
        bool searchStudent = false;     //A boolean to difference the search button function.

        public Form1()
        {
            InitializeComponent();
            course = new Course(courseName);   //set the course name while the app started.
            rbGroup.Checked = true;             //set default the radio button to be selected in group.
        }

        //Just to make sure that the ID input is integer.
        private void tbIDNum_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
        }

        //Just to make sure that the search index input is integer, but only when the search student boolean is true.
        private void tbSearch_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (rbStudent.Checked == true)
            {
                e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
            }
        }

        //To setup the search student boolean via radio buttons' check changes.
        private void rbGroup_CheckedChanged(object sender, EventArgs e)
        {
            tbSearch.Text = "";
            searchStudent = false;
        }
        private void rbStudent_CheckedChanged(object sender, EventArgs e)
        {
            tbSearch.Text = "";
            searchStudent = true;
        }

        private void tbSearch_TextChanged(object sender, EventArgs e)
        {
            TextBox text = (TextBox)sender;
            lbData.Items.Clear();
            if (searchStudent == false)
            {
                foreach (ProjectGroup group in course.Groups) 
                {
                    if (group.GroupName.IndexOf(text.Text, StringComparison.OrdinalIgnoreCase) >= 0) 
                    {
                        lbData.Items.Add(group.GroupName);
                    }
                }
            }
            else
            {
                foreach (Student student in course.Students)
                {
                    if (student.StudentNumber.ToString().IndexOf(text.Text, StringComparison.OrdinalIgnoreCase) >= 0) 
                    {
                        lbData.Items.Add($"{student.GetInfo()}");
                    }
                }
            }
        }

        private void CleanEntryTextBox()
        {
            tbIDNum.Text = "";
            tbName.Text = "";
        }

        //Adding student with the name, ID number, and group name in a course.
        private void AddStudents()
        {
            couldAdd = course.AddStudent(name, idNum);
            if (couldAdd == false)
            {
                MessageBox.Show($"Sorry! student {name} or id {idNum} was already registered before!");
            }
            else
            {
                showStudents();
            }
        }

        //show the added students.
        private void showStudents() 
        {
            lbData.Items.Clear();
            foreach (Student students in course.Students) 
            {
                lbData.Items.Add($"{students.GetInfo()}");
            }
        }

        //show the made out group.
        private void showGroups()
        {
            lbData.Items.Clear();
            foreach (ProjectGroup group in course.Groups)
            {
                lbData.Items.Add(group.GroupName);
            }
        }

        //show the course info.
        private void showCourseInfo()
        {
            lbData.Items.Clear();
            lbData.HorizontalScrollbar = true;
            lbData.Items.Add($"There are {course.StudentsCount} students and {course.GroupsCount} groups in {course.Name} class.");
        }

        //The Add student input
        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (tbName.Text == "" && tbIDNum.Text == "")
            {
                MessageBox.Show("Please add the student name and the ID number first!");
            }
            else if (tbName.Text == "")
            {
                MessageBox.Show("Please add the student name first!");
            }
            else if (tbIDNum.Text == "")
            {
                MessageBox.Show("Please add the ID number name first!");
            }
            else
            {
                int entryNumber = Convert.ToInt32(tbIDNum.Text);
                if (entryNumber >= 10000)                  ///////////////////////////////////////////////////////////////////////////// make sure that the student id is >= 10000 or -1 (invalid)
                {
                    if (Regex.IsMatch(tbName.Text.Trim(), @"[0-9]"))            //////////////////////////////////////////////////////// make sure that the student name is not containing any numbers.
                    {
                        MessageBox.Show("Sorry! We cannot add any name that contains numbers!");
                        tbName.Text = "";
                    }
                    else
                    {
                        name = tbName.Text;
                        idNum = entryNumber;
                        AddStudents();                  //To add the student by using a method above.
                        CleanEntryTextBox();            //To empty some text boxes instantly.
                    }
                }
                else
                {
                    MessageBox.Show("Sorry! The input ID should be 5 digit numbers or more!");
                    tbIDNum.Text = "";
                }
            }
        }

        //The Search input
        private void btnSearch_Click(object sender, EventArgs e)
        {
            string input = tbSearch.Text;
            if (input == "")
            {
                MessageBox.Show("Please write your search input first!");
            }
            else
            {
                if (searchStudent == false)
                {
                    string groupIndex = tbSearch.Text;
                    Student[] groups = course.SearchByGroup(groupIndex);
                    lbData.Items.Clear();
                    lbData.Items.Add($"Students in {groupIndex} are: ");
                    lbData.Items.Add("");

                    if (groups.Count() >= 1)
                    {
                        foreach (Student student in groups)
                        {
                            lbData.Items.Add(student.GetInfo());
                        }
                    }
                    else
                    {
                        lbData.Items.Add("None.");
                    }
                }
                else
                {
                    int searchId = Convert.ToInt32(tbSearch.Text);
                    Student students = course.SearchByStudentNumber(searchId);
                    if (students == null) 
                    {
                        MessageBox.Show("This student ID is not in the list!");
                        return;
                    }
                    lbData.Items.Clear();
                    lbData.Items.Add($"{students.GetInfo()}");
                }
            }
        }

        //The show info input
        private void btnShow_Click(object sender, EventArgs e)
        {
            lbData.Items.Clear();
            if (cbSelections.Text == "")
            {
                MessageBox.Show("Please select what data you want to show first!");
            }
            else if (cbSelections.SelectedIndex == 0)
            {
                showStudents();
            }
            else if (cbSelections.SelectedIndex == 1)
            {
                showGroups();
            }
            else if (cbSelections.SelectedIndex == 2) 
            {
                showCourseInfo();
            }
        }
    }
}