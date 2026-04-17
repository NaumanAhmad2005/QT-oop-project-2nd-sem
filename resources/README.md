# Application Resources

Place your application resources in this folder:

## Icons
- `app_icon.png` - Main application icon (256x256 recommended)
- `app_icon.ico` - Windows icon file

## Images
- `logo.png` - Application logo for about dialog
- `background.png` - Any background images used in the UI

## How to Add Resources

1. Add your image files to this folder
2. Update `resources.qrc` in the root directory:

```xml
<qresource prefix="/">
    <file>resources/app_icon.png</file>
    <file>resources/logo.png</file>
</qresource>
```

3. Rebuild the project
4. Use in code: `QPixmap(":/logo.png")`
