using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    public abstract class Device
    {
        private string deviceName;
        private int deviceID;
        private string userName;

        /// <summary>
        /// Initialize the Device class.
        /// </summary>
        /// <param name="id">The unique ID of the device.</param>
        /// <param name="name">The name of the device.</param>
        public Device(int id, string name)
        {
            this.deviceID = id;
            this.deviceName = name;
            this.userName = "";
        }

        public int Id { get => deviceID; }

        public string Name { get => deviceName; }

        public string User { get => userName; }

        /// <summary>
        /// Check if the selected device has a user or not.
        /// </summary>
        /// <returns> true or false </returns>
        private bool IsAssigned()
        {
            return userName != "";
        }

        /// <summary>
        /// Assigns device to a user by adding the user name to the selected device.
        /// </summary>
        /// <param name="deviceID">The ID number of the device.</param>
        /// <param name="userName">A Name of the user(player) who want to borrow the device</param>
        public void AssignDevice(int deviceID, string userName)
        {
            if (IsAssigned())
            {
                throw new DeviceIsAlreadyAssignedException(deviceID);
            }
            else 
            {
                this.userName = userName;
                throw new DeviceSuccessfullyAssigned(deviceID, userName);
            }
        }

        /// <summary>
        /// Returns device from a user by removing its user name.
        /// </summary>
        /// <param name="deviceID">The ID of the device.</param>
        public void ReturnDevice(int deviceID)
        {
            if (IsAssigned())
            {
                this.userName = "";
                throw new DeviceSuccessfullyReturned(deviceID);
            }
            else
            {
                throw new ReturnUnassignedDeviceException(deviceID);
            }
        }

        /// <summary>
        /// Get all of the devices' details per type.
        /// </summary>
        /// <returns>A string of detailed information of device.</returns>
        public virtual string GetDetails()
        {
            return $"{this.GetType().Name}: ID: {this.deviceID}, Name: {this.deviceName}";
        }
    }
}
