using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace project_climate_control_app
{
    class Receiver
    {
        private SubForms.RoomClimateData roomData = SubForms.Rooms.DataCloud;
        bool ConnectionStatus = false;

        private Thread receivingThread;
        private Thread sendingThread;
        public Server Server { get; set; }
        public TcpClient Client { get; set; }
        public List<String> MessageQueue { get; private set; }


        public Receiver(TcpClient client, Server server)
        {
            MessageQueue = new List<String>();
            Server = server;
            Client = client;
            Client.ReceiveBufferSize = 1024;
            Client.SendBufferSize = 1024;
            ConnectionStatus = true;
        }

        public void Start()
        {
            receivingThread = new Thread(ReceivingMethod);
            receivingThread.IsBackground = true;
            receivingThread.Start();

            sendingThread = new Thread(SendingMethod);
            sendingThread.IsBackground = true;
            sendingThread.Start();
        }

        private void Disconnect()
        {
            if (!ConnectionStatus) return;
            ConnectionStatus = false;
            Client.Client.Disconnect(false);
            Client.Close();
        }


        private void SendingMethod()
        {
            while (ConnectionStatus)
            {
                if (MessageQueue.Count > 0)
                {
                    var message = MessageQueue[0];
                    try
                    {
                        NetworkStream clientStream = Client.GetStream();
                        StreamWriter streamWriter = new StreamWriter(clientStream);
                        streamWriter.Write(message);
                        streamWriter.Flush();
                    }
                    catch
                    {
                        Disconnect();
                    }
                    finally
                    {
                        MessageQueue.RemoveAt(0);
                    }
                }
                Thread.Sleep(30);
            }
        }

        private void ReceivingMethod()
        {
            while (ConnectionStatus)
            {
                if (Client.Available > 0)
                {
                    try
                    {
                        NetworkStream clientStream = Client.GetStream();
                        StreamReader streamReader = new StreamReader(clientStream);
                        char[] puchBuffer = new char[Client.Available];
                        int iQtt = streamReader.Read(puchBuffer, 0, Client.Available);
                        string msg = String.Empty;
                        for (int i = 0; i < puchBuffer.Length; i++)
                        {
                            msg = $"{msg}{Convert.ToString(puchBuffer[i])}";
                        }
                        OnMessageReceived(msg);
                    }
                    catch (Exception)
                    {

                    }
                }
                Thread.Sleep(30);
            }
        }

        private void OnMessageReceived(String msg)
        {
            roomData.readInputMessage(msg);
        }
    }
}
