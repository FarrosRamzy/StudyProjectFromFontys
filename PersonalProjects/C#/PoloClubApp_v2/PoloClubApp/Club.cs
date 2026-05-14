using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PoloClubApp
{
    class Club
    {
        private Device device;
        private string name;            // the name of the club
        private List<Device> devices;   // a list of devices

        /// <summary>
        /// Initialize the Club class.
        /// </summary>
        /// <param name="name">The name of the app.</param>
        public Club(string name)
        {
            this.name = name;
            this.devices = new List<Device>();
        }

        public string Name {get { return this.name; } } // read only property for Name


        //-----Provide your answers here-----


        /// <summary>
        /// Provides all wearable devices to the caller.
        /// </summary>
        /// <returns>List of wearables</returns>
        public List<Device> GetAllWearables() 
        {
            List<Device> Wearables = new List<Device>();
            foreach (Device device in devices)
            {
                if (device is IWearable)
                {
                    Wearables.Add(device);
                }
            }
            return Wearables;
        }


        /// <summary>
        /// Assigns the selected device to a user by checking the availability of the selected device ID.
        /// </summary>
        /// <param name="deviceID">The unique ID of the device that will be assigned.</param>
        /// <param name="userName">The name of the user who want to borrow the device from the list.</param>
        public void AssignDevice(int deviceID, string userName)
        {
            device = this.GetDeviceById(deviceID);
            if (device is IWearable)
            {
                if (((IWearable)device).GetWaterResistanceMeters() <= 3)
                {
                    throw new UnacceptedResistanceMeterException(deviceID);
                }
                else
                {
                    device.AssignDevice(deviceID, userName);
                }
            }
            else
            {
                device.AssignDevice(deviceID, userName);
            }
        }


        /// <summary>
        /// Returns the selected device by its ID, only if it is already assigned.
        /// </summary>
        /// <param name="deviceID">The unique ID of the device that will be returned.</param>
        public void ReturnDevice(int deviceID)
        {
            device = this.GetDeviceById(deviceID);
            device.ReturnDevice(deviceID);
        }


        /// <summary>
        /// Provides all devices that are assigned on a player.
        /// </summary>
        /// <param name="userName">The name of the user(player) in question.</param>
        /// <returns>List of assigned device to the user(player).</returns>
        public List<Device> GetAllAssignedDevicesPerPlayer(string userName) 
        {
            List<Device> assignedDevices = new List<Device>();
            foreach (Device device in devices)
            {
                if (device.User == userName)
                {
                    assignedDevices.Add(device);
                }
            }
            return assignedDevices;
        }


        /// <summary>
        /// Provides a report of a player and all assigned devices in details.
        /// </summary>
        /// <param name="userName">The name of the user(player) in question.</param>
        /// <returns>A list of report from the user(player) in question.</returns>
        public List<String> GenerateReportPerPlayer(string userName) 
        {
            List<String> generatedReport = new List<String>();
            
            int numberOfDevices = 0;
            int numberOfPhones = 0;
            int numberOfWearables = 0;
            
            generatedReport.Add($"List of devices assigned to {userName}:\n");
            generatedReport.Add($"=================================================\n");
            generatedReport.Add($"Phones:\n");
            generatedReport.Add($"-----------\n");

            foreach (Device device in GetAllAssignedDevicesPerPlayer(userName))
            {
                if (device is SmartPhone)
                {
                    generatedReport.Add($"      {device.GetDetails()}\n");
                    numberOfPhones++;
                    numberOfDevices++;
                }
            }

            generatedReport.Add($"IWearables:\n");
            generatedReport.Add($"-----------\n");

            foreach (Device device in GetAllAssignedDevicesPerPlayer(userName))
            {
                if (device is IWearable)
                {
                    if (device is SmartWatch)
                    {
                        generatedReport.Add($"      {((SmartWatch)device).GetDetails()}\n");
                    }
                    else if (device is FitTracker)
                    {
                        generatedReport.Add($"      {((FitTracker)device).GetDetails()}\n");
                    }
                    numberOfWearables++;
                    numberOfDevices++;
                }
            }

            generatedReport.Add($"----------------------------------------------------------------\n");
            generatedReport.Add($"Total: {numberOfDevices} Devices ({numberOfPhones} Phones And {numberOfWearables} IWearable Devices)");

            return generatedReport;
        }


        // -----The provided code below will not be graded, therefore should not be changed-----


        /// <summary>
        /// Provides all devices to the caller.
        /// </summary>
        /// <returns>List of devices</returns>
        public List<Device> GetAllDevices()
        {
            return this.devices;
        }


        /// <summary>
        /// Adds a device to the list of devices if unique id is provided.
        /// </summary>
        /// <param name="device">device to be added</param>
        public void AddDevice(Device device)
        {
            foreach (Device dev in this.devices)
            {
                if (dev.Id == device.Id)
                {
                    return;
                }
            }
            devices.Add(device);
        }
        

        /// <summary>
        /// Provides a device by a given id.
        /// </summary>
        /// <param name="id">the unique identity number of the requested device.</param>
        /// <returns>A device when found, otherwise null</returns>
        public Device GetDeviceById(int id)
        {
            foreach (Device dev in this.devices)
            {
                if (dev.Id == id)
                {
                    return dev;
                }
            }
            return null;
        }

    }
}
