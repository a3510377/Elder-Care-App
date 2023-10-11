window.onload = async () => {
  window.ui = SwaggerUIBundle({
    url: 'swagger.json',
    dom_id: '#swagger-ui',
    deepLinking: !0,
    presets: [SwaggerUIBundle.presets.apis, SwaggerUIStandalonePreset],
    plugins: [SwaggerUIBundle.plugins.DownloadUrl],
    layout: 'StandaloneLayout',
  });
};
