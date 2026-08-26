#!/usr/bin/env python3
"""Convert C++ files to HTML-safe versions for embedding"""

import os
import html
from pathlib import Path

def cpp_file_to_html(cpp_filename, output_dir="html-output"):
    """Convert a .cpp file into an embeddable HTML snippet"""
    
    with open(f"cpp-examples/{cpp_filename}", "r", encoding="utf-8") as f:
        code = f.read()

    # Escape special characters for safe HTML embedding
    escaped_code = html.escape(code)

    filename_no_ext = Path(cpp_filename).stem  # Remove .cpp extension
    
    html_content = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{filename_no_ext}</title>
    <!-- Prism.js for syntax highlighting -->
    <link href="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/themes/prism.min.css" rel="stylesheet"/>
    <style>
        body {{ margin: 0; padding: 20px; font-family: Arial, sans-serif; }}
        pre {{ border-radius: 6px; padding: 15px !important; }}
        .code-container {{ position: relative; }}
        .copy-btn {{
            position: absolute; top: 10px; right: 10px;
            background-color: #4CAF50; color: white; border: none;
            padding: 6px 12px; border-radius: 4px; cursor: pointer;
        }}
    </style>
</head>
<body>

<div class="code-container">
<pre><code class="language-cpp">{escaped_code}</code></pre>
<button class="copy-btn" onclick="navigator.clipboard.writeText(`{code}`)">Copy Code</button>
</div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/components/prism-core.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/prism/1.29.0/plugins/autoloader/prism-autoloader.min.js"></script>

</body>
</html>"""

    output_path = Path(output_dir) / f"{filename_no_ext}.html"
    with open(output_path, "w", encoding="utf-8") as out:
        out.write(html_content)

if __name__ == "__main__":
    os.makedirs("html-output", exist_ok=True)
    
    for cpp_file in Path("cpp-examples").glob("*.cpp"):
        try:
            cpp_file_to_html(cpp_file.name)
            print(f"✅ Converted {cpp_file.name}")
        except Exception as e:
            print(f"❌ Failed to convert {cpp_file.name}: {e}")
