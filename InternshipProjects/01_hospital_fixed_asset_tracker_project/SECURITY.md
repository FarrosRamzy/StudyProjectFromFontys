# Security Notes

This repository is an internship prototype and should not be deployed in a hospital without a separate production security review.

## Secret handling

I keep database URLs, JWT secrets, MQTT credentials, and deployment-specific values outside the documentation and source-control history. Local `.env` files must remain untracked.

Before making the repository public, the firmware configuration also needs review. Development setup credentials and provisioning values currently represented in the firmware source should be replaced with a secure provisioning process and rotated before deployment.

## Production checklist

- Use HTTPS and secure WebSocket connections.
- Use authenticated MQTT access and an isolated topic namespace.
- Store secrets in the deployment platform or another protected secret store.
- Restrict CORS origins to the intended frontends.
- Disable or restrict interactive API documentation in production.
- Replace development provisioning credentials and access-point passwords.
- Apply database migrations and backups through a documented process.
- Review user roles and test the last-active-admin safety rules.
- Avoid storing patient identifiers or clinical records.
- Validate node installation, power, wiring, and radio behavior at the deployment site.

## Reporting a security issue

Security issues should be reported privately to the repository owner rather than opened as a public issue. A report should include the affected component, reproduction steps, expected impact, and any suggested mitigation.
