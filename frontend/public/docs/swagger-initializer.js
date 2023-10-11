window.onload = async () => {
  window.ui = SwaggerUIBundle({
    url: 'https://raw.githubusercontent.com/a3510377/Elder-Care-App/assets/swagger.json',
    dom_id: '#swagger-ui',
    deepLinking: !0,
    presets: [SwaggerUIBundle.presets.apis, SwaggerUIStandalonePreset],
    plugins: [SwaggerUIBundle.plugins.DownloadUrl],
    layout: 'StandaloneLayout',
  });
};
