(self.webpackChunklite=self.webpackChunklite||[]).push([[8978],{18978:(e,n,i)=>{"use strict";i.d(n,{L:()=>g});var t=i(67294),l=i(71652),o=i(82405),a=i(25735),r=i(73279),c=i(4381),d=i(77355),u=i(27323),s=i(20113),m=i(87691),p=i(92780),v=i(14646),f=i(21372),k=i(68427),g=function(e){var n=e.collection,i=e.buttonSize,r=e.buttonStyleFn,c=n.name,u=n.description;return(0,a.V)({name:"enable_updated_pub_recs_ui",placeholder:!1})?t.createElement(w,{collection:n}):t.createElement(d.x,{padding:"15px",display:"flex",flexDirection:"column",width:"300px"},t.createElement(d.x,{display:"flex",flexDirection:"row",justifyContent:"space-between",whiteSpace:"normal",borderBottom:"neutral.primary",paddingBottom:"10px",marginBottom:"10px"},t.createElement(d.x,{display:"flex",flexDirection:"column",paddingRight:"5px"},t.createElement(s.X6,{scale:"S"},c),t.createElement(m.F,{scale:"S"},u)),t.createElement(d.x,null,t.createElement(l.v,{collection:n,link:!0}))),t.createElement(d.x,{display:"flex",flexDirection:"row",alignItems:"center",justifyContent:"space-between"},t.createElement(m.F,{scale:"M"},"Followed by ",(0,f.pY)(n.subscriberCount||0)," people"),t.createElement(o.F,{collection:n,buttonSize:i,buttonStyleFn:r,susiEntry:"follow_card"})))},w=function(e){var n,i,a=e.collection,s=a.name,g=a.description,w=a.customStyleSheet,E=(0,k.R)(a),b=(0,p.n)({name:"heading",scale:"XS",clamp:2,fontWeight:"NORMAL",color:"NORMAL"}),x=(0,v.I)();return t.createElement(d.x,{width:"280px",display:"flex",flexDirection:"column",padding:"24px",position:"relative"},(null==w||null===(n=w.header)||void 0===n||null===(i=n.backgroundImage)||void 0===i?void 0:i.id)&&t.createElement(d.x,{position:"absolute",top:"0",left:"0",borderRadius:"4px 4px 0 0",overflow:"hidden"},t.createElement(c.UV,{miroId:w.header.backgroundImage.id,height:42,width:280})),t.createElement(d.x,{display:"flex",flexDirection:"row",justifyContent:"space-between",alignItems:"flex-end"},t.createElement(l.v,{size:64,collection:a,link:!0}),t.createElement(d.x,null,t.createElement(o.F,{collection:a,buttonSize:"SMALL",buttonStyleFn:function(e){return e?"SUBTLE":"BRAND"},susiEntry:"follow_card"}))),t.createElement(d.x,{marginTop:"12px",display:"flex",flexDirection:"column"},t.createElement(u.P,{href:E},t.createElement(d.x,{display:"flex",flexDirection:"column"},t.createElement("div",{className:x([b,{display:"block"}])},s))),t.createElement(d.x,{marginTop:"4px",display:"flex",flexDirection:"row"},t.createElement(m.F,{scale:"S",color:"LIGHTER"},"Publication"),t.createElement(r.O,{margin:"0 8px"}),t.createElement(m.F,{scale:"S"},(0,f.pY)(a.subscriberCount||0)," Followers"))),g&&t.createElement(d.x,{paddingTop:"12px"},t.createElement(m.F,{scale:"S",color:"DARKER"},g)))}},68427:(e,n,i)=>{"use strict";i.d(n,{B:()=>r,R:()=>c});var t=i(8575),l=i(67294),o=i(43487),a=i(78870),r=function(){var e=(0,o.v9)((function(e){return e.navigation.currentLocation})),n=(0,o.v9)((function(e){return e.config.authDomain})),i=(0,a.rp)();return(0,l.useCallback)((function(l){var o=l.id,a=l.domain,r=function(e){var n=e.id,i=e.slug;return i?"/".concat(i):"/c/".concat(n)}({id:o,domain:a,slug:l.slug});if(i)return"https://".concat(n).concat(r);var c=(0,t.parse)(e).port;return a?"https://".concat(a).concat(c?":".concat(c):""):"https://".concat(n).concat(r)}),[i])},c=function(e){return r()(e)}},71652:(e,n,i)=>{"use strict";i.d(n,{v:()=>s});var t=i(67294),l=i(68427),o=i(14818),a=i(4381),r=i(27323),c=i(29746),d=i(46696),u=function(e){return function(n){return{border:"1px solid rgba(0, 0, 0, 0.05)",borderRadius:(0,c.a)(n.borderRadius.regular),width:(0,c.a)(e),height:(0,c.a)(e)}}},s=function(e){var n=e.circular,i=e.collection,c=e.size,s=void 0===c?60:c,m=e.link,p=e.showHoverState,v=(0,l.R)(i);if(!i||!i.avatar||!i.avatar.id)return null;var f=i.avatar.id,k=i.name||"Publication avatar",g=n?t.createElement(o.z,{miroId:f,alt:k,diameter:s,freezeGifs:!1,showHoverState:p}):t.createElement(a.UV,{rules:[u(s)],miroId:f,alt:k,width:s,height:s,strategy:d._S.Crop});return m?t.createElement(r.P,{href:v},g):g}},82405:(e,n,i)=>{"use strict";i.d(n,{F:()=>S});var t=i(34699),l=i(21919),o=i(67294),a=i(51615),r=i(77520),c=i(20297),d=i(25550),u=i(25267),s=i(39727),m=i(26350),p=i(50563),v=i(93310),f=i(77355),k=i(47230),g=i(18627),w=i(66411),E=i(92661),b=i(43487),x=i(50458),S=function(e){var n,i=e.buttonSize,x=e.buttonStyleFn,S=e.collection,F=e.post,h=e.simpleLink,C=e.susiEntry,N=void 0===C?"follow_card":C,D=e.preventParentClick,I=e.width,_=(0,b.v9)((function(e){return e.config.authDomain})),R=(0,d.r)().viewerId,T=(0,g.A)(),z=(0,w.pK)(),L=(0,a.TH)(),V=(0,E.$B)(L.pathname),B=null==V||null===(n=V.route)||void 0===n?void 0:n.name,O=(0,s.g)(S),A=O.viewerEdge,U=O.loading,P=function(e,n){var i=(0,l.D)(c.e),a=(0,t.Z)(i,1)[0];return o.useCallback((function(){return a({variables:{id:e.id},optimisticResponse:{followCollection:{__typename:"Collection",id:e.id,name:e.name,viewerEdge:{__typename:"CollectionViewerEdge",id:"collectionId:".concat(e.id,"-viewerId:").concat(n),isFollowing:!0}}},update:function(i){i.modify({id:"User:".concat(n),fields:{missionControl:(0,p.im)("followedCollections",!0),followingCollectionConnection:(0,p.Hc)(e.id)}})}})}),[e.id])}(S,R),H=function(e,n){var i=(0,l.D)(c.X),a=(0,t.Z)(i,1)[0];return o.useCallback((function(){return a({variables:{id:e.id},optimisticResponse:{unfollowCollection:{__typename:"Collection",id:e.id,name:e.name,viewerEdge:{__typename:"CollectionViewerEdge",id:"collectionId:".concat(e.id,"-viewerId:").concat(n),isFollowing:!1}}},update:function(e){e.modify({id:"User:".concat(n),fields:{missionControl:(0,p.im)("followedCollections",!1)}})}})}),[e.id])}(S,R),M=o.useCallback((function(e){D&&e.preventDefault(),T.event("collection.followed",{collectionId:S.id,followSource:z}),P()}),[S,D,z,T]),j=o.useCallback((function(e){D&&e.preventDefault(),T.event("collection.unfollowed",{collectionId:S.id,followSource:z}),H()}),[D,z,T]),G=!(null==A||!A.isFollowing),W=x?x(!!G):G?"OBVIOUS":"STRONG";return h?o.createElement(v.r,{onClick:G?j:M},o.createElement(f.x,{display:"flex",flexDirection:"row"},G?"Unfollow publication":"Follow publication")):o.createElement(u.I,null,(function(e){return e?o.createElement(k.zx,{size:i,onClick:G?j:M,buttonStyle:W,loading:U,width:I},G?"Following":"Follow"):o.createElement(m.R,{collection:S,buttonStyle:W,isButton:!0,buttonSize:i,operation:"register",actionUrl:y(_,S,F)||"",susiEntry:N,pageSource:(0,r.x)(B,"register"),buttonWidth:I},G?"Following":"Follow")}))},y=function(e,n,i){return n.slug&&(i&&i.id?(0,x.TAb)(e,n.slug,i.id):(0,x.LlO)(e,n.slug))}},39727:(e,n,i)=>{"use strict";i.d(n,{g:()=>a});var t=i(64718),l=i(87329),o={kind:"Document",definitions:[{kind:"OperationDefinition",operation:"query",name:{kind:"Name",value:"CollectionViewerEdge"},variableDefinitions:[{kind:"VariableDefinition",variable:{kind:"Variable",name:{kind:"Name",value:"collectionId"}},type:{kind:"NonNullType",type:{kind:"NamedType",name:{kind:"Name",value:"ID"}}}}],selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"collection"},arguments:[{kind:"Argument",name:{kind:"Name",value:"id"},value:{kind:"Variable",name:{kind:"Name",value:"collectionId"}}}],selectionSet:{kind:"SelectionSet",selections:[{kind:"InlineFragment",typeCondition:{kind:"NamedType",name:{kind:"Name",value:"Collection"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"viewerEdge"},selectionSet:{kind:"SelectionSet",selections:[{kind:"FragmentSpread",name:{kind:"Name",value:"Collection_viewerEdge"}}]}}]}}]}}]}}].concat((0,l.Z)([{kind:"FragmentDefinition",name:{kind:"Name",value:"Collection_viewerEdge"},typeCondition:{kind:"NamedType",name:{kind:"Name",value:"CollectionViewerEdge"}},selectionSet:{kind:"SelectionSet",selections:[{kind:"Field",name:{kind:"Name",value:"id"}},{kind:"Field",name:{kind:"Name",value:"canEditOwnPosts"}},{kind:"Field",name:{kind:"Name",value:"canEditPosts"}},{kind:"Field",name:{kind:"Name",value:"isEditor"}},{kind:"Field",name:{kind:"Name",value:"isFollowing"}},{kind:"Field",name:{kind:"Name",value:"isMuting"}},{kind:"Field",name:{kind:"Name",value:"isSubscribedToLetters"}},{kind:"Field",name:{kind:"Name",value:"isSubscribedToMediumNewsletter"}},{kind:"Field",name:{kind:"Name",value:"isSubscribedToEmails"}},{kind:"Field",name:{kind:"Name",value:"isWriter"}}]}}]))},a=function(e){var n,i,l=(0,t.a)(o,{variables:{collectionId:null!==(n=null==e?void 0:e.id)&&void 0!==n?n:""},ssr:!1,skip:!(null!=e&&e.id)}),a=l.loading,r=l.error,c=l.data;return a?{loading:a}:r?{error:r}:{viewerEdge:null==c||null===(i=c.collection)||void 0===i?void 0:i.viewerEdge}}},25267:(e,n,i)=>{"use strict";i.d(n,{I:()=>l});var t=i(6443),l=function(e){var n=e.children,i=e.nonBlocking,l=(0,t.H)(),o=l.error,a=l.loading,r=l.value;return i&&(o||a)?n(null):a?null:n(r)}}}]);
//# sourceMappingURL=https://stats.medium.build/lite/sourcemaps/8978.98aa973b.chunk.js.map