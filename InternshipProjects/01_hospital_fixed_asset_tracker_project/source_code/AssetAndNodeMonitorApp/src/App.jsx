/**
 * @file App.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-12

 * @Copyright (c) 2026
 */

import { useState } from "react";
import { AppLayout } from "./components/layout/AppLayout";
import { useMonitorData } from "./hooks/useMonitorData";
import { useMonitorSocket } from "./hooks/socket/useMonitorSocket";

import { DashboardPage } from "./pages/DashboardPage";
import { AssetMonitorPage } from "./pages/AssetMonitorPage";
import { NodeMonitorPage } from "./pages/NodeMonitorPage";
import { AlertsPage } from "./pages/AlertsPage";
import { ActivityPage } from "./pages/ActivityPage";

export default function App() {
    const [activePage, setActivePage] = useState("dashboard");

    const {
        assets,
        setAssets,
        nodes,
        setNodes,
        alerts,
        setAlerts,
        activity,
        setActivity,
        loading,
        error,
    } = useMonitorData();

    const { wsStatus } = useMonitorSocket({
        setAssets,
        setNodes,
        setAlerts,
        setActivity,
    });

    function renderPage() {
        if (loading) {
            return (
                <div className="rounded-3xl border border-slate-800 bg-slate-900/70 p-8 text-center text-slate-400">
                    Loading monitor data...
                </div>
            );
        }

        if (error) {
            return (
                <div className="rounded-3xl border border-red-500/20 bg-red-500/10 p-8 text-center text-red-100">
                    {error}
                </div>
            );
        }

        switch (activePage) {
            case "assets":
                return <AssetMonitorPage assets={assets} />;

            case "nodes":
                return <NodeMonitorPage nodes={nodes} />;

            case "alerts":
                return <AlertsPage alerts={alerts} />;

            case "activity":
                return <ActivityPage activity={activity} />;

            case "dashboard":
            default:
                return (
                    <DashboardPage
                        assets={assets}
                        nodes={nodes}
                        alerts={alerts}
                        activity={activity}
                    />
                );
        }
    }

    return (
        <AppLayout
            activePage={activePage}
            setActivePage={setActivePage}
            wsStatus={wsStatus}
        >
            {renderPage()}
        </AppLayout>
    );
}

// import { useState } from 'react'
// import reactLogo from './assets/react.svg'
// import viteLogo from './assets/vite.svg'
// import heroImg from './assets/hero.png'
// import './App.css'

// function App() {
//   const [count, setCount] = useState(0)

//   return (
//     <>
//       <section id="center">
//         <div className="hero">
//           <img src={heroImg} className="base" width="170" height="179" alt="" />
//           <img src={reactLogo} className="framework" alt="React logo" />
//           <img src={viteLogo} className="vite" alt="Vite logo" />
//         </div>
//         <div>
//           <h1>Get started</h1>
//           <p>
//             Edit <code>src/App.jsx</code> and save to test <code>HMR</code>
//           </p>
//         </div>
//         <button
//           type="button"
//           className="counter"
//           onClick={() => setCount((count) => count + 1)}
//         >
//           Count is {count}
//         </button>
//       </section>

//       <div className="ticks"></div>

//       <section id="next-steps">
//         <div id="docs">
//           <svg className="icon" role="presentation" aria-hidden="true">
//             <use href="/icons.svg#documentation-icon"></use>
//           </svg>
//           <h2>Documentation</h2>
//           <p>Your questions, answered</p>
//           <ul>
//             <li>
//               <a href="https://vite.dev/" target="_blank">
//                 <img className="logo" src={viteLogo} alt="" />
//                 Explore Vite
//               </a>
//             </li>
//             <li>
//               <a href="https://react.dev/" target="_blank">
//                 <img className="button-icon" src={reactLogo} alt="" />
//                 Learn more
//               </a>
//             </li>
//           </ul>
//         </div>
//         <div id="social">
//           <svg className="icon" role="presentation" aria-hidden="true">
//             <use href="/icons.svg#social-icon"></use>
//           </svg>
//           <h2>Connect with us</h2>
//           <p>Join the Vite community</p>
//           <ul>
//             <li>
//               <a href="https://github.com/vitejs/vite" target="_blank">
//                 <svg
//                   className="button-icon"
//                   role="presentation"
//                   aria-hidden="true"
//                 >
//                   <use href="/icons.svg#github-icon"></use>
//                 </svg>
//                 GitHub
//               </a>
//             </li>
//             <li>
//               <a href="https://chat.vite.dev/" target="_blank">
//                 <svg
//                   className="button-icon"
//                   role="presentation"
//                   aria-hidden="true"
//                 >
//                   <use href="/icons.svg#discord-icon"></use>
//                 </svg>
//                 Discord
//               </a>
//             </li>
//             <li>
//               <a href="https://x.com/vite_js" target="_blank">
//                 <svg
//                   className="button-icon"
//                   role="presentation"
//                   aria-hidden="true"
//                 >
//                   <use href="/icons.svg#x-icon"></use>
//                 </svg>
//                 X.com
//               </a>
//             </li>
//             <li>
//               <a href="https://bsky.app/profile/vite.dev" target="_blank">
//                 <svg
//                   className="button-icon"
//                   role="presentation"
//                   aria-hidden="true"
//                 >
//                   <use href="/icons.svg#bluesky-icon"></use>
//                 </svg>
//                 Bluesky
//               </a>
//             </li>
//           </ul>
//         </div>
//       </section>

//       <div className="ticks"></div>
//       <section id="spacer"></section>
//     </>
//   )
// }

// export default App
