(self.webpackChunklite=self.webpackChunklite||[]).push([[6046],{41135:(e,n,t)=>{"use strict";t.d(n,{b:()=>O});var i=t(96156),a=t(67294),r=t(33380),o=t(87329),d=t(38883),l=t(94124),m=t(96370),c=t(14646),s=t(75221),u=t(32342);function p(e,n){var t=Object.keys(e);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);n&&(i=i.filter((function(n){return Object.getOwnPropertyDescriptor(e,n).enumerable}))),t.push.apply(t,i)}return t}function g(e){for(var n=1;n<arguments.length;n++){var t=null!=arguments[n]?arguments[n]:{};n%2?p(Object(t),!0).forEach((function(n){(0,i.Z)(e,n,t[n])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(t)):p(Object(t)).forEach((function(n){Object.defineProperty(e,n,Object.getOwnPropertyDescriptor(t,n))}))}return e}var k={clear:"both"},f={clear:"both",width:"100%"},h=function(e){var n,t,i=e.layoutGroup,r=e.postBodyInserts,o=(0,c.I)(),s=i.styleGroups[0].paragraphViewModels[0].richTextStyle,p=i.styleGroups.map((function(e,n){var t=n<3;return a.createElement(d.ZQ,{key:n,styleGroup:e,postBodyInserts:r,loading:t?l.K.EAGER:l.K.LAZY})}));if((0,u.jH)(s)||"INLINE"===s)return a.createElement(a.Fragment,null,p);switch(i.effectiveLayout){case"OUTSET_CENTER":case"OUTSET_ROW":return a.createElement("div",{className:o(k)},a.createElement(m.P,{size:{xs:"full",sm:"full",md:"full",lg:"outset",xl:"outset"}},p));case"FULL_WIDTH":return a.createElement("div",{className:o(f)},p);default:return"FULL_PAGE"===s?a.createElement(m.P,{size:"app"},p):a.createElement("div",{className:o((n=i.effectiveLayout,t={boxSizing:"border-box",margin:"0 auto",width:"100%"},"INSET_CENTER"===n?g(g({},t),{},{maxWidth:"700px",padding:"0 1.25em"}):t))},p)}},v=a.memo(h),N=t(98096),y=t(31889),S={":after":{display:"block",content:'""',clear:"both"}},F=t(46696),E=t(3207);function b(e,n){var t=Object.keys(e);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);n&&(i=i.filter((function(n){return Object.getOwnPropertyDescriptor(e,n).enumerable}))),t.push.apply(t,i)}return t}function P(e){for(var n=1;n<arguments.length;n++){var t=null!=arguments[n]?arguments[n]:{};n%2?b(Object(t),!0).forEach((function(n){(0,i.Z)(e,n,t[n])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(t)):b(Object(t)).forEach((function(n){Object.defineProperty(e,n,Object.getOwnPropertyDescriptor(t,n))}))}return e}var _=function(){return{display:"table-cell",paddingBottom:"32px",verticalAlign:"bottom"}};function x(e){var n,t,i,o,d=e.bgImage,l=e.children,m=e.isFullPage,s=e.paragraphName,u=(0,c.I)(),p=(0,y.F)();return d&&d.id&&m?a.createElement(r.TA,{name:s,type:"bgimage"},a.createElement("div",{className:u((n=d,t=n.id,i=n.originalWidth,o=n.originalHeight,function(){var e=[400,600,800,1e3,1200,1400,1600,1800,2e3],n={miroId:t,strategy:F._S.Resample,verticalGradient:{start:29,end:81,opacity:40}},a=e.reduce((function(t,a,r){var d=(0,F.W6)(P(P({},n),{},{width:a,height:a/i*o}));return r===e.length-1?(t.backgroundImage="url(".concat(d,")"),t):(t["@media (min-width: ".concat(a,"px)")]={backgroundImage:"url(".concat(d,")")},t)}),{});return P({backgroundColor:"rgba(0, 0, 0, 0.9)",backgroundPosition:"50% 50%",backgroundSize:"cover",display:"table",minHeight:"100vh",width:"100%"},a)}))},a.createElement("div",{className:u(_)},a.createElement(N.f,{theme:(0,E.GV)(p)},l)))):l}var O=function(e){var n=e.paragraphViewModels,t=e.postBodyInserts,i=e.section,r=(0,c.I)();if(0===n.length)return null;var l=function(e){var n=[],t=[];e.forEach((function(e){var i=function(e,n){switch(n){case s.ms.INSET_LEFT:case s.ms.OUTSET_LEFT:return"IMG"===e||"IFRAME"===e?s.ms.INSET_CENTER:n;case s.ms.OUTSET_ROW_CONTINUE:return s.ms.OUTSET_ROW;default:return n||s.ms.INSET_CENTER}}(e.paragraphStyle,e.paragraph.layout),a=n[n.length-1];if(a&&a.effectiveLayout===i)t.push(e);else{if(a){var r,l=(0,d.lD)(t);(r=a.styleGroups).push.apply(r,(0,o.Z)(l))}t.length=0,t.push(e),n.push({styleGroups:[],effectiveLayout:i})}}));var i=n[n.length-1];if(i){var a,r=(0,d.lD)(t);(a=i.styleGroups).push.apply(a,(0,o.Z)(r))}return n}(n),m=function(e){switch(e){case"SERIES":return{paddingTop:"32px",paddingBottom:"32px",margin:"auto 0",width:"100%"};case"STREAM":case"CARD":case"FULL_PAGE":case"INLINE":return{wordBreak:"break-word",wordWrap:"break-word"};default:return{}}}(n[0].richTextStyle);return a.createElement("div",{className:r([m,S])},a.createElement(x,{bgImage:i.backgroundImage,isFullPage:"FULL_PAGE"===n[0].richTextStyle,paragraphName:n[0].paragraph.name},l.map((function(e,n){return a.createElement(v,{key:n,layoutGroup:e,postBodyInserts:t})}))))}},94078:(e,n,t)=>{"use strict";t.d(n,{Pk:()=>E,v:()=>P,XV:()=>b,w6:()=>_});var i=t(87329),a=t(82717),r=t(93235),o=t(50207),d={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"IframeParagraph_paragraph"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Paragraph"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"type"}},{kind:"Field",name:{kind:"Name",value:"iframe"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"mediaResource"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"iframeSrc"}},{kind:"Field",name:{kind:"Name",value:"iframeHeight"}},{kind:"Field",name:{kind:"Name",value:"iframeWidth"}},{kind:"Field",name:{kind:"Name",value:"title"}}]}}]}},{kind:"Field",name:{kind:"Name",value:"layout"}},{kind:"FragmentSpread",name:{kind:"Name",value:"Markups_paragraph"}}]}}].concat((0,i.Z)(o.Zr.definitions))},l=t(78882),m={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodyParagraph_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"TextParagraph_highlight"}},{kind:"FragmentSpread",name:{kind:"Name",value:"ImageParagraph_highlight"}}]}}].concat((0,i.Z)(a.m8.definitions),(0,i.Z)(r.Zl.definitions))},c={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodyParagraph_privateNote"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Note"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"TextParagraph_privateNote"}},{kind:"FragmentSpread",name:{kind:"Name",value:"ImageParagraph_privateNote"}}]}}].concat((0,i.Z)(a.hz.definitions),(0,i.Z)(r.T_.definitions))},s={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodyParagraph_paragraph"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Paragraph"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"name"}},{kind:"Field",name:{kind:"Name",value:"type"}},{kind:"FragmentSpread",name:{kind:"Name",value:"ImageParagraph_paragraph"}},{kind:"FragmentSpread",name:{kind:"Name",value:"TextParagraph_paragraph"}},{kind:"FragmentSpread",name:{kind:"Name",value:"IframeParagraph_paragraph"}},{kind:"FragmentSpread",name:{kind:"Name",value:"MixtapeParagraph_paragraph"}},{kind:"FragmentSpread",name:{kind:"Name",value:"CodeBlockParagraph_paragraph"}}]}}].concat((0,i.Z)(r.ck.definitions),(0,i.Z)(a.Rg.definitions),(0,i.Z)(d.definitions),(0,i.Z)(l.b.definitions),(0,i.Z)([{kind:"FragmentDefinition",name:{kind:"Name",value:"CodeBlockParagraph_paragraph"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Paragraph"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"codeBlockMetadata"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"lang"}},{kind:"Field",name:{kind:"Name",value:"mode"}}]}}]}}]))},u={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"ParagraphStyleGrouping_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodyParagraph_highlight"}}]}}].concat((0,i.Z)(m.definitions))},p={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"ParagraphStyleGrouping_privateNote"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Note"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodyParagraph_privateNote"}}]}}].concat((0,i.Z)(c.definitions))},g={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"ParagraphLayoutGrouping_privateNote"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Note"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"ParagraphStyleGrouping_privateNote"}}]}}].concat((0,i.Z)(p.definitions))},k={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"ParagraphLayoutGrouping_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"ParagraphStyleGrouping_highlight"}}]}}].concat((0,i.Z)(u.definitions))},f={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodySection_paragraph"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Paragraph"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"name"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodyParagraph_paragraph"}}]}}].concat((0,i.Z)(s.definitions))},h={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodySection_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"ParagraphLayoutGrouping_highlight"}}]}}].concat((0,i.Z)(k.definitions))},v={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBodySection_privateNote"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Note"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"ParagraphLayoutGrouping_privateNote"}}]}}].concat((0,i.Z)(g.definitions))},N=t(54975),y=t(27048),S={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostNotesDetails_user"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"User"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"imageId"}},{kind:"Field",name:{kind:"Name",value:"name"}},{kind:"Field",name:{kind:"Name",value:"username"}},{kind:"FragmentSpread",name:{kind:"Name",value:"UserAvatar_user"}}]}}].concat((0,i.Z)(y.W.definitions))},F={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostNotesMarkers_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"endOffset"}},{kind:"Field",name:{kind:"Name",value:"paragraphs"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"name"}}]}},{kind:"Field",name:{kind:"Name",value:"startOffset"}},{kind:"Field",name:{kind:"Name",value:"userId"}},{kind:"Field",name:{kind:"Name",value:"user"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"name"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostNotesDetails_user"}}]}}]}}].concat((0,i.Z)(S.definitions))},E={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBody_bodyModel"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"RichText"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"sections"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"name"}},{kind:"Field",name:{kind:"Name",value:"startIndex"}},{kind:"Field",name:{kind:"Name",value:"textLayout"}},{kind:"Field",name:{kind:"Name",value:"imageLayout"}},{kind:"Field",name:{kind:"Name",value:"backgroundImage"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"originalHeight"}},{kind:"Field",name:{kind:"Name",value:"originalWidth"}}]}},{kind:"Field",name:{kind:"Name",value:"videoLayout"}},{kind:"Field",name:{kind:"Name",value:"backgroundVideo"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"videoId"}},{kind:"Field",name:{kind:"Name",value:"originalHeight"}},{kind:"Field",name:{kind:"Name",value:"originalWidth"}},{kind:"Field",name:{kind:"Name",value:"previewImageId"}}]}}]}},{kind:"Field",name:{kind:"Name",value:"paragraphs"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodySection_paragraph"}}]}},{kind:"FragmentSpread",name:{kind:"Name",value:"normalizedBodyModel_richText"}}]}}].concat((0,i.Z)(f.definitions),(0,i.Z)(N.gd.definitions))},b={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBody_highlight"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Quote"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"paragraphs"},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}}]}},{kind:"FragmentSpread",name:{kind:"Name",value:"getParagraphHighlights_highlight"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodySection_highlight"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostNotesMarkers_highlight"}}]}}].concat((0,i.Z)(N.W$.definitions),(0,i.Z)(h.definitions),(0,i.Z)(F.definitions))},P={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBody_creator"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"User"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"PostNotesMarkers_creator"}}]}}].concat((0,i.Z)([{kind:"FragmentDefinition",name:{kind:"Name",value:"PostNotesMarkers_creator"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"User"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"name"}}]}}]))},_={kind:"Document",definitions:[{kind:"FragmentDefinition",name:{kind:"Name",value:"PostBody_privateNote"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Note"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"normalizedBodyModel_privateNote"}},{kind:"FragmentSpread",name:{kind:"Name",value:"PostBodySection_privateNote"}}]}}].concat((0,i.Z)(N.EH.definitions),(0,i.Z)(v.definitions))}},90504:(e,n,t)=>{"use strict";t.d(n,{y:()=>Q});var i=t(22122),a=t(87329),r=t(67294),o=t(33380),d=t(14646),l={display:"flex",justifyContent:"center",marginTop:"32px",marginBottom:"14px",paddingTop:"24px",paddingBottom:"10px"},m=function(e){return{backgroundColor:e.colorTokens.foreground.neutral.primary.hover,borderRadius:"50%",display:"inline-block",height:"3px",width:"3px"}},c={marginRight:"20px"};function s(){var e=(0,d.I)();return r.createElement("div",{className:e(l),role:"separator"},r.createElement("span",{className:e([m,c])}),r.createElement("span",{className:e([m,c])}),r.createElement("span",{className:e(m)}))}var u=t(41135),p=t(34699),g=t(90484),k=t(23450),f=t.n(k),h=t(17193),v=t(77355),N=t(8431),y=t(31889),S=t(34135);function F(e){var n=e.grid.xStep;return{padding:"".concat(3*n,"px ").concat(4*n,"px ").concat(3*n,"px"),width:"400px"}}function E(e){var n=e.close,t=e.users,i=(0,d.I)(),a=r.useRef(null),o=(0,y.F)(),l=o.grid.xStep;return r.useEffect((function(){function e(){var e=a.current;if(e&&e.getBoundingClientRect){var t=e.getBoundingClientRect(),i=t.bottom,r=t.top<0||i>window.innerHeight,d=window.innerWidth<o.breakpoints.xl;(r||d)&&n()}}return S.V6.on("scroll_end",e),S.V6.on("resize_throttled",e),function(){S.V6.off("scroll_end",e),S.V6.off("resize_throttled",e)}}),[]),r.createElement("section",{ref:a,className:i(F)},r.createElement(v.x,{borderBottom:"neutral.primary",marginBottom:"-".concat(l,"px"),paddingBottom:"".concat(2*l,"px")},r.createElement(N.Lh,null,"Highlights (".concat(t.length,")"))),r.createElement(v.x,{marginLeft:"3px"},t.length&&t.map((function(e){return r.createElement(v.x,{display:"inline-block",key:e.id,marginTop:"".concat(5*l,"px"),marginRight:"".concat(5*l,"px"),width:"".concat(8*l,"px")},r.createElement(h.Yt,{hasPopover:!0,link:!0,user:e,scale:"XS"}))}))))}var b=r.memo(E),P=t(83363),_=t(69217),x=t(60748),O=t(25267),T=t(61095),w=t(66227),I=t(87691),D=t(29746),Z=t(39202);function B(){return{border:"none",cursor:"pointer",display:"block",padding:"0px",textAlign:"left",width:"100%"}}function C(){return{left:"100%",position:"absolute",top:0}}function R(e,n){return{marginTop:"6px",maxWidth:"100%",position:"absolute",top:"".concat(e-(n||0),"px"),whiteSpace:"nowrap",width:"100%"}}function L(e){return{marginLeft:"auto",marginRight:"auto",maxWidth:"".concat((0,D.G)(e,8,!0),"px"),position:"relative"}}function j(){return{display:"inline-block",maxWidth:"100%",whiteSpace:"nowrap",overflow:"hidden",textOverflow:"ellipsis"}}function G(e,n){return"number"==typeof e.startOffset&&"number"==typeof n.startOffset?e.startOffset<n.startOffset?-1:1:-1}function M(e,n){var t=n.startOffset,i=n.endOffset,a=n.paragraphs[0].name;if(!a||"number"!=typeof t||"number"!=typeof i)return e;var r=!1,o=e[a]||[];return o.length&&(o=o.map((function(e){var a=t<=e.endOffset+1,o=e.startOffset,d=e.endOffset;return a&&(r=!0,e.highlights.push(n),d=Math.max(i,e.endOffset),o=Math.min(t,e.startOffset)),{highlights:e.highlights,endOffset:d,startOffset:o}}))),r||o.push({highlights:[n],endOffset:i,startOffset:t}),e[a]=o,e}function A(e){var n=e.children,t=e.highlightString,i=e.toggle,a=(0,d.I)();return"Top highlight"===t?r.createElement(r.Fragment,null,n):r.createElement("button",{className:a(B),onClick:function(){return i()},onMouseDown:function(e){return e.preventDefault()}},n)}function H(e){var n=e.creator,t=e.positionMap,i=e.yPosOffset,a=e.viewerEdge,o=(0,d.I)();if("number"!=typeof i)return null;var l=Array.from(t.entries());return r.createElement(O.I,{nonBlocking:!0},(function(e){return r.createElement(r.Fragment,null,l.map((function(t,d){var l=(0,p.Z)(t,2),m=l[0],c=l[1],s=function(e,n,t,i){var a=null==i?void 0:i.isFollowing;if(1===e.length){if("anon"===e[0].userId)return"Top highlight";if(!n)return null;if(t&&t.id===e[0].userId&&n.id!==t.id&&!a)return null;if(n&&n.id===e[0].userId)return"You highlighted";if(e[0].user&&e[0].user.name)return e[0].user.name}var r=[];if(e.forEach((function(e){if(e.user){var i=n&&n.id===e.userId,o=e.user.name,d=t&&t.id===e.userId&&(!n||n.id!==t.id&&!a);i?r.length&&"You"===r[0]||r.unshift("You"):d||!o||r.includes(o)||r.push(o)}})),!r.length)return"Top highlight";if(1===r.length)return"You"===r[0]?"You highlighted":r[0];if(2===r.length)return"".concat(r[0]," and ").concat(r[1]);var o=r.slice(0,2),d=r.length-o.length;return"".concat(o[0],", ").concat(o[1],", and ").concat(d," ").concat(f()("other",d))}(c,e,n,a);return s?r.createElement("div",{className:o(R(m,i)),key:d},r.createElement(w.B,null,(function(e){var n=e.isVisible,t=e.hide,i=e.toggle;return r.createElement(r.Fragment,null,r.createElement(A,{toggle:i,highlightString:s},r.createElement(I.F,{scale:"S"},r.createElement("span",{className:o(j)},s))),n&&r.createElement(_.G,{boundariesElement:"document",isVisible:!0,hide:t,placement:"right",popoverRenderFn:function(){var e=new Set,n=c.map((function(n){var t=n.user;return t&&t.id&&!e.has(t.id)?(e.add(t.id),t):null})).filter(Z.bb);return r.createElement(b,{close:t,users:n})}},r.createElement(r.Fragment,null)))}))):null})))}))}var W=r.forwardRef((function(e,n){var t=e.creator,i=e.highlights,o=r.useContext(P.V).highlightSegments,l=r.useRef(null),m=r.useState(null),c=(0,p.Z)(m,2),s=c[0],u=c[1],k=(0,d.I)(),f=(0,y.F)(),h=r.useState(null),N=(0,p.Z)(h,2),F=N[0],E=N[1],b=r.useState(null),_=(0,p.Z)(b,2),O=_[0],w=_[1],I=(0,T.Pd)(t).viewerEdge;return r.useEffect((function(){var e=function(){var e=function(e,n,t){var i=new Map;if(e.size&&n.length){var r=function(e){var n=(0,a.Z)(e).sort(G).reduce(M,{});return Object.values(n).reduce((function(e,n){return n&&"object"===(0,g.Z)(n)&&n.length?(e.push.apply(e,(0,a.Z)(n)),e):e}),[])}(n),o=[];r.forEach((function(n){var a=n.highlights[0],r=a.paragraphs[0].name;if(a&&"number"==typeof a.startOffset&&r){var d=e.get("".concat(r,"_").concat(a.startOffset));if(d&&d.ref&&d.ref.current){var l,m=d.ref.current.getBoundingClientRect().top+window.pageYOffset;o.length&&(l=o.find((function(e){return m<e+t.newFonts.body.lineHeight.M&&m>e||m>e-t.newFonts.body.lineHeight.M&&m<e})));var c=l||m,s=i.get(c)||[];s.length||o.push(c);var u=s.concat(n.highlights);u.length&&i.set(c,u)}}}))}return i}(o,i,f);if(u(e),"function"!=typeof n&&null!=n&&n.current&&w(n.current.offsetTop),null!=l&&l.current){var t=l.current.getBoundingClientRect().left,r=window.innerWidth-t-8*f.grid.xStep;E(r)}};S.V6.on("resize_throttled",e);var t=(0,x.x)((function(n){"iframe.resize"!==n.context&&"player.js"!==n.context||e()})).destructor;return e(),function(){S.V6.off("resize_throttled",e),t()}}),[i,o]),r.createElement("div",{className:k(L)},r.createElement(v.x,{display:"block",xs:{display:"none"},sm:{display:"none"},md:{display:"none"},lg:{display:"none"},speechifyIgnore:!0},r.createElement("aside",{className:k(C),ref:l,style:{width:F?"".concat(F,"px"):void 0}},s&&r.createElement(H,{creator:t,highlights:i,positionMap:s,yPosOffset:O,width:F,viewerEdge:I}))))})),U=r.memo(W),V=t(75119);function z(e,n){var t;return Object.keys(e).some((function(i){return!!e[i].find((function(e){return e.insertType===n}))&&(t=i,!0)})),t}var Y=t(32342),Q=r.forwardRef((function(e,n){var t,l,m=e.bodyModel,c=e.creator,p=e.highlights,g=e.isAuroraPostPageEnabled,k=e.privateNotes,f=e.postBodyInserts,h=e.richTextStyle,v=void 0===h?"FULL_PAGE":h,N=e.shouldHideHighlightAnnotations,y=void 0!==N&&N,S=(0,d.I)(),F=r.createRef(),E=null===(t=r.useContext(o.u6).watchedBounds.get("byline"))||void 0===t||null===(l=t.ref)||void 0===l?void 0:l.current,b=E?E.offsetTop-48:100,P={position:"absolute",left:0,top:"calc(100vh + ".concat(b,"px)"),bottom:"calc(100vh + ".concat(100,"px)"),width:"10px",pointerEvents:"none"},_=(0,V.Z)().privateNoteSelection,x=r.useMemo((function(){return p&&_?[].concat((0,a.Z)(p),[_]):p}),[p,_]),O=f?function(e){return z(e,"BYLINE")}(f):void 0,T=f?function(e){return z(e,"METER")}(f):void 0,w=r.useMemo((function(){return(0,Y.fj)(m,{bylineParagraphName:O,meterParagraphName:T,highlights:x,isAuroraPostPageEnabled:g,isPostPage:!0,privateNotes:k,richTextStyle:v})}),[m,x,k,v]),I=f&&f.first;return r.createElement("section",{ref:n},r.createElement("div",{ref:F},r.createElement(r.Fragment,null,r.createElement(o.TA,{name:"ghost-track",type:"ghost",className:S(P)}),"FULL_PAGE"===v&&p&&p.length>0&&!y&&r.createElement(U,{creator:c,highlights:(0,a.Z)(p),ref:n}),!!I&&I.map((function(e,n){return e.component?r.createElement("div",{key:"postBodyInsertFirst_".concat(n)},e.component):null}))),w.map((function(e,n){if("HR"===e){var t,a,o=w[n-1],d=w[n+1],l="HR"!==o&&(null==o||null===(t=o.section)||void 0===t?void 0:t.backgroundImage),m="HR"!==d&&(null==d||null===(a=d.section)||void 0===a?void 0:a.backgroundImage);return l||m?null:r.createElement(s,{key:n})}return r.createElement(u.b,(0,i.Z)({key:e.section.name||n,postBodyInserts:f},e))}))))}))}}]);
//# sourceMappingURL=https://stats.medium.build/lite/sourcemaps/6046.f9be485b.chunk.js.map