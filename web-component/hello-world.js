const template = document.createElement('template');
template.innerHTML = `
    <style>
        /* Add your component's CSS here */
    </style>
    <p>Hello, <slot></slot></p>
`;

class HelloWorld extends HTMLElement {
    constructor() {
        super();
        const templateContent = template.content.cloneNode(true);
        this.attachShadow({ mode: 'open' }).appendChild(templateContent);
    }
}

customElements.define('hello-world', HelloWorld);