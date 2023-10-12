<script lang="ts" setup>
let { pageTitle, baseTitle } = defineProps({
  pageTitle: { default: '安全居家' },
  baseTitle: { default: ' | Elder-Care-App' },
});

onMounted(() => {
  useHead({ title: pageTitle + baseTitle });
});
</script>
