using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Threading;

namespace project_climate_control_app
{
    class Server
    {
        private SubForms.RoomClimateData roomData = SubForms.Rooms.DataCloud;
        private TcpListener server = null;
        private bool serverAdded;
        public bool GetServerInfo { get => serverAdded; }

        public Server(string ip, int port)
        {
            IPAddress localAddr = IPAddress.Parse(ip);
            server = new TcpListener(localAddr, port);

            if (!serverAdded)
            {
                serverAdded = true;
                server.Start();
            }
            else if (serverAdded)
            {
                StartListener();
            }
        }

        public void StartListener()
        {
            try
            {
                TcpClient client = server.AcceptTcpClient();
                if (client != null)
                {
                    Thread t = new Thread(new ParameterizedThreadStart(HandleRooms));
                    t.Start(client);
                }
            }
            catch (SocketException)
            {
                serverAdded = false;
                server.Stop();
            }
        }

        public void HandleRooms(Object obj)
        {
            TcpClient client = (TcpClient)obj;
            var stream = client.GetStream();

            string data = null;
            Byte[] bytes = new Byte[256];
            int i;
            try
            {
                while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                {
                    string hex = BitConverter.ToString(bytes);
                    data = Encoding.ASCII.GetString(bytes, 0, i);
                    roomData.readInputMessage(data);
                }
            }
            catch (Exception)
            {
                //client.Close();
            }
        }
    }
}
