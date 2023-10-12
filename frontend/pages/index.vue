<template>
  <GeneralHead />
  <div class="w-full flex flex-col justify-center items-center text-white">
    <h1 class="text-2xl sm:text-4xl md:text-6xl uppercase text-center mb-5">
      <span class="block">安全居家</span>
      <span class="block">Elder Care App</span>
    </h1>
    <div class="flex gap-5">
      <NuxtLink
        href="https://a3510377.github.io/Elder-Care-App/docs"
        no-rel
        target="_blank"
        class="text-xl bg-gray-800 px-5 py-4 rounded flex items-center"
      >
        Docs
        <Icon name="material-symbols:docs" size="28" class="ml-2" />
      </NuxtLink>
      <NuxtLink
        href="https://github.com/a3510377/Elder-Care-App"
        no-rel
        target="_blank"
        class="text-xl bg-gray-800 px-5 py-4 rounded flex items-center"
      >
        Github
        <Icon name="mdi:github-face" size="28" class="ml-2" />
      </NuxtLink>
    </div>
  </div>
</template>
