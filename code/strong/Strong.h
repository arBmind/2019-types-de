#pragma once

// tag::strong[]
template<class V, class... /*Tags*/>
struct Strong {
    V v{};
};
// end::strong[]

template<class T>
struct Type;

template<class Tag, class V, class... Tags>
auto strongAddTag(Type<Strong<V, Tags...>>) -> Strong<V, Tags..., Tag>;

template<class Strong, class Tag>
using StrongAddTag = decltype(strongAddTag<Tag>(Type<Strong>{}));
