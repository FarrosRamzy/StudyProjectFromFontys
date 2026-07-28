/**
 * @file SystemSettings.jsx
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-06-23

 * @Copyright (c) 2026
 */


import MessageBanner from "../components/common/MessageBanner";
import MqttSettingsForm from "../components/settings/MqttSettingsForm";
import RegistrationModuleNav from "../components/common/RegistrationModuleNav";
import RegistrationTopbar from "../components/common/RegistrationTopbar";
import { useAuth } from "../context/AuthContext";
import { useMqttSettingsForm } from "../hooks/settings/useMqttSettingsForm";
import { useAuthActions } from "../hooks/useAuthAction";

export default function SystemSettings() {
    const { user } = useAuth();
    const { handleLogout } = useAuthActions();
    const settings = useMqttSettingsForm();

    return (
        <main className="app-shell">
            <div className="sticky-page-header">
                <RegistrationTopbar
                    user={user}
                    subtitle="System Settings"
                    onRefresh={settings.reloadSettings}
                    onLogout={handleLogout}
                />
                <RegistrationModuleNav role={user?.role} />
            </div>

            <section className="page-hero">
                <div className="hero-main">
                    <p className="eyebrow">Admin Configuration</p>
                    <h1>MQTT Settings</h1>
                    <p className="hero-copy">
                        Configure the broker and hospital namespace used by
                        the backend and newly provisioned nodes.
                    </p>
                </div>
            </section>

            <MessageBanner error={settings.error} successMessage={settings.message} />

            <section className="panel settings-panel">
                <div className="section-header">
                    <div>
                        <h2>MQTT Broker Setup</h2>
                        <p>
                            Enter the hospital name, broker link, and port. The
                            app generates the hospital ID and namespace.
                        </p>
                    </div>
                </div>

                {settings.loading ? (
                    <p>Loading MQTT settings...</p>
                ) : (
                    <MqttSettingsForm
                        form={settings.form}
                        preview={settings.preview}
                        saving={settings.saving}
                        onFieldChange={settings.updateField}
                        onSubmit={settings.saveSettings}
                        onReconnect={settings.reconnect}
                        onReset={settings.resetToDefault}
                    />
                )}
            </section>
        </main>
    );
}
